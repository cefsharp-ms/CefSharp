#include "stdafx.h"
#include "JavascriptAsyncPropertyHandler.h"
#include "../CefSharp.Core/Internals/Messaging/Messages.h"
#include "../CefSharp.Core/Internals/Serialization/Primitives.h"
#include "Serialization/V8Serialization.h"
#include "CefAppUnmanagedWrapper.h"

#include "include/cef_worker_context.h"

using namespace CefSharp::Internals::Messaging;
using namespace CefSharp::Internals::Serialization;


bool JavascriptAsyncPropertyHandler::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval,
    CefString& exception)
{
    auto context = CefV8Context::GetCurrentContext();

    if (context.get() && context->Enter())
    {
        try
        {
            auto request = CefProcessMessage::Create(kJavascriptAsyncPropertyGetRequest);
            auto argList = request->GetArgumentList();

            auto frame = context->GetFrame();
            long frameId = -1;
            if (frame)
            {
                frameId = frame->GetIdentifier();
            }
            SetInt64(argList, 0, frameId);
            SetInt64(argList, 1, _objectId);
            argList->SetString(2, name);

            auto browser = context->GetBrowser();

            if (browser.get())
            {
                auto result = browser->SendSyncProcessMessage(CefProcessId::PID_BROWSER, request);
                auto argList = result->GetArgumentList();
                auto success = argList->GetBool(0);
                if (success)
                {
                    retval = DeserializeV8Object(argList, 1);
                }
                else
                {
                    exception = argList->GetString(1);
                }
            }
            else
            {
                return false;
            }
        }
        finally
        {
            context->Exit();
        }
    }

    return true;
}

bool JavascriptAsyncPropertyHandler::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value,
    CefString& exception)
{
    auto context = CefV8Context::GetCurrentContext();

    if (context.get() && context->Enter())
    {
        try
        {
            auto request = CefProcessMessage::Create(kJavascriptAsyncPropertySetRequest);
            auto argList = request->GetArgumentList();

            auto frame = context->GetFrame();
            long frameId = -1;
            if (frame)
            {
                frameId = frame->GetIdentifier();
            }
            SetInt64(argList, 0, frameId);
            SetInt64(argList, 1, _objectId);
            argList->SetString(2, name);
            SerializeV8Object(value, argList, 3, _callbackRegistry);

            auto browser = context->GetBrowser();

            if (browser.get())
            {
                auto result = browser->SendSyncProcessMessage(CefProcessId::PID_BROWSER, request);
                auto argList = result->GetArgumentList();
                auto success = argList->GetBool(0);
                if (!success)
                {
                    exception = argList->GetString(1);
                }
            }
            else
            {
                return false;
            }
        }
        finally
        {
            context->Exit();
        }
    }

    return true;
}
