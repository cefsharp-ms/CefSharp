#include "Stdafx.h"

#include "WorkerBindingManager.h"
#include "CefSharpApp.h"

using namespace CefSharp::Internals;

WorkerBindingManager::WorkerBindingManager(CefRefPtr<CefSharpApp> cefSharpApp, JavascriptObjectRepository^ objectRepository)
    :_cefSharpApp(cefSharpApp)
{
    _methodRunnerQueue = gcnew MethodRunnerQueue(objectRepository);
    _methodRunnerQueue->MethodInvocationComplete += gcnew EventHandler<MethodInvocationCompleteArgs^>(this, &WorkerBindingManager::MethodInvocationComplete);
    _methodRunnerQueue->Start();

    _pendingTaskRepository = gcnew PendingTaskRepository<JavascriptResponse^>();
    _javascriptCallbackFactory = gcnew CefSharp::Internals::JavascriptCallbackFactory(_pendingTaskRepository);
}

void WorkerBindingManager::Enqueue(MethodInvocation^ invocation)
{
    _methodRunnerQueue->Enqueue(invocation);
}

void WorkerBindingManager::MethodInvocationComplete(Object^ sender, MethodInvocationCompleteArgs^ e)
{
    _cefSharpApp->MethodInvocationComplete(e);
}
