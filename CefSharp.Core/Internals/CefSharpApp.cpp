#include "Stdafx.h"

#include "include/cef_process_message.h"
#include "CefSharpApp.h"
#include "Serialization\Primitives.h"
#include "Serialization\V8Serialization.h"
#include "Serialization\JsObjectsSerialization.h"
#include "Serialization\ObjectsSerialization.h"
#include "Messaging\Messages.h"

using namespace CefSharp::Internals;
using namespace CefSharp::Internals::Messaging;
using namespace CefSharp::Internals::Serialization;

void CefSharpApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extraInfo)
{
    auto extensionList = CefListValue::Create();

    auto i = 0;
    for each(V8Extension^ cefExtension in _cefSettings->Extensions)
    {
        auto ext = CefListValue::Create();
        ext->SetString(0, StringUtils::ToNative(cefExtension->Name));
        ext->SetString(1, StringUtils::ToNative(cefExtension->JavascriptCode));
        extensionList->SetList(i++, ext);
    }

    if (CefSharpSettings::JavascriptObjectRepository->HasBoundObjects && CefSharpSettings::LegacyJavascriptBindingEnabled)
    {
        SerializeJsObjects(CefSharpSettings::JavascriptObjectRepository->GetObjects(nullptr), extraInfo, 1);
    }

    extraInfo->SetList(0, extensionList);
}

bool  CefSharpApp::OnWorkerProcessMessageReceived(CefRefPtr<CefWorkerContext> context, CefRefPtr<CefProcessMessage> message)
{
    auto argList = message->GetArgumentList();
    auto name = message->GetName();
    if (name == kJavascriptAsyncMethodCallRequest)
    {
        auto frameId = 0;
        auto objectId = GetInt64(argList, 1);
        auto callbackId = GetInt64(argList, 2);
        auto methodName = StringUtils::ToClr(argList->GetString(3));
        auto arguments = argList->GetList(4);

        auto id = ++_lastId;
        _contexts.insert(std::make_pair(id, context));

        auto methodInvocation = gcnew MethodInvocation(id, frameId, objectId, methodName, (callbackId > 0 ? Nullable<int64>(callbackId) : Nullable<int64>()));
        for (auto i = 0; i < static_cast<int>(arguments->GetSize()); i++)
        {
            methodInvocation->Parameters->Add(DeserializeObject(arguments, i, _workerBindingsManager->CallbackFactory));
        }

        _workerBindingsManager->Enqueue(methodInvocation);
    }

    return true;
}

void CefSharpApp::MethodInvocationComplete(MethodInvocationCompleteArgs^ e)
{
    auto result = e->Result;
    if (result->CallbackId.HasValue)
    {
        auto message = CefProcessMessage::Create(kJavascriptAsyncMethodCallResponse);
        auto argList = message->GetArgumentList();
        SetInt64(argList, 0, result->FrameId);
        SetInt64(argList, 1, result->CallbackId.Value);
        argList->SetBool(2, result->Success);
        if (result->Success)
        {
            SerializeV8Object(argList, 3, result->Result);
        }
        else
        {
            argList->SetString(3, StringUtils::ToNative(result->Message));
        }

        auto it = _contexts.find(result->BrowserId);
        if (it != _contexts.end()) {
            it->second->Send(CefProcessId::PID_RENDERER, message);
            _contexts.erase(it);

        }
    }
}
