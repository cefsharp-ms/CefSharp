#pragma once

#include "include/cef_v8.h"
#include "JavascriptCallbackRegistry.h"
#include "JavascriptAsyncMethodCallback.h"

namespace CefSharp
{
    namespace Internals
    {
        namespace Async
        {
            private class JavascriptAsyncPropertyHandler : public CefV8Accessor
            {
            private:
                gcroot<JavascriptCallbackRegistry^> _callbackRegistry;

                int64 _objectId;

            public:
                JavascriptAsyncPropertyHandler(int64 objectId, JavascriptCallbackRegistry^ callbackRegistry)
                    :_callbackRegistry(callbackRegistry), _objectId(objectId)
                {

                }

                virtual bool Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& retval,
                    CefString& exception) override;

                virtual bool Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value,
                    CefString& exception) override;

                IMPLEMENT_REFCOUNTING(JavascriptAsyncPropertyHandler)
            };
        }
    }
}
