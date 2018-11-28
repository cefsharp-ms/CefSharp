#pragma once

#include "JavascriptAsyncPropertyHandler.h"
#include "JavascriptCallbackRegistry.h"

namespace CefSharp
{
    namespace Internals
    {
        namespace Async
        {
            private ref class JavascriptAsyncPropertyWrapper
            {
            private:
                initonly JavascriptProperty^ _prop;
                initonly JavascriptCallbackRegistry^ _callbackRegistry;
                initonly Func<JavascriptAsyncMethodCallback^, int64>^ _methodCallbackSave;
                Object^ _javascriptObjectWrapper;
                MCefRefPtr<JavascriptAsyncPropertyHandler> _javascriptMethodHandler;

            public:
                JavascriptAsyncPropertyWrapper(int64 ownerId, JavascriptProperty^ prop, JavascriptCallbackRegistry^ callbackRegistry, Func<JavascriptAsyncMethodCallback^, int64>^ methodCallbackSave)
                    : _javascriptMethodHandler(new JavascriptAsyncPropertyHandler(ownerId, callbackRegistry)), _prop(prop), _callbackRegistry(callbackRegistry), _methodCallbackSave(methodCallbackSave)
                {

                }

                ~JavascriptAsyncPropertyWrapper()
                {
                    if (_javascriptObjectWrapper != nullptr)
                    {
                        delete _javascriptObjectWrapper;
                        _javascriptObjectWrapper = nullptr;
                    }
                }

                void Bind(const CefRefPtr<CefV8Value>& value);
            };
        }
    }
}
