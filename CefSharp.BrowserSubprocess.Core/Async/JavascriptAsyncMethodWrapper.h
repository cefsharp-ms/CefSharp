// Copyright © 2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "JavascriptAsyncMethodHandler.h"
#include "JavascriptCallbackRegistry.h"

namespace CefSharp
{
    namespace Internals
    {
        namespace Async
        {
            private ref class JavascriptAsyncMethodWrapper
            {
            private:
                initonly JavascriptMethod^ _method;
                MCefRefPtr<JavascriptAsyncMethodHandler> _javascriptMethodHandler;

            public:
                JavascriptAsyncMethodWrapper(int64 ownerId, JavascriptMethod^ method, JavascriptCallbackRegistry^ callbackRegistry, Func<JavascriptAsyncMethodCallback^, int64>^ methodCallbackSave)
                    : _javascriptMethodHandler(new JavascriptAsyncMethodHandler(ownerId, callbackRegistry, methodCallbackSave, method->FireAndForget, method->Sync)), _method(method)
                {

                }

                void Bind(const CefRefPtr<CefV8Value>& value);
            };
        }
    }
}
