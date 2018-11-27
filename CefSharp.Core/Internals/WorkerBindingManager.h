#pragma once

#include "Stdafx.h"
#include "include/cef_app.h"

#include "Internals/JavascriptCallbackFactory.h"

namespace CefSharp
{
    class CefSharpApp;

    namespace Internals
    {
        private ref class WorkerBindingManager
        {
        private:
            MethodRunnerQueue ^ _methodRunnerQueue;
            JavascriptCallbackFactory ^ _javascriptCallbackFactory;
            PendingTaskRepository<JavascriptResponse^>^ _pendingTaskRepository;
            MCefRefPtr<CefSharpApp> _cefSharpApp;

            void MethodInvocationComplete(Object^ sender, MethodInvocationCompleteArgs^ e);
        public:
            property JavascriptCallbackFactory^ CallbackFactory
            {
                JavascriptCallbackFactory ^ get()
                {
                    return _javascriptCallbackFactory;
                }
            }

            WorkerBindingManager(CefRefPtr<CefSharpApp> cefSharpApp, JavascriptObjectRepository^ objectRepository);

            void Enqueue(MethodInvocation^ invocation);
        };
    }
}
