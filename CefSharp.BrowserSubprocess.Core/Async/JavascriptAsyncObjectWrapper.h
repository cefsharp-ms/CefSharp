// Copyright © 2015 The CefSharp Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.

#pragma once

#include "JavascriptAsyncMethodCallback.h"
#include "JavascriptCallbackRegistry.h"
#include "JavascriptAsyncMethodWrapper.h"
#include "JavascriptAsyncPropertyWrapper.h"

namespace CefSharp
{
    namespace Internals
    {
        namespace Async
        {
            private ref class JavascriptAsyncObjectWrapper
            {
            private:
                initonly List<JavascriptAsyncMethodWrapper^>^ _wrappedMethods;
                initonly List<JavascriptAsyncPropertyWrapper^>^ _wrappedProperties;
                Func<JavascriptAsyncMethodCallback^, int64>^ _methodCallbackSave;
                JavascriptCallbackRegistry^ _callbackRegistry;
                MCefRefPtr<JavascriptAsyncPropertyHandler> _jsPropertyHandler;

            public:
                JavascriptAsyncObjectWrapper(JavascriptCallbackRegistry^ callbackRegistry, Func<JavascriptAsyncMethodCallback^, int64>^ saveMethod)
                    : _wrappedMethods(gcnew List<JavascriptAsyncMethodWrapper^>()), _wrappedProperties(gcnew List<JavascriptAsyncPropertyWrapper^>()),
                      _methodCallbackSave(saveMethod), _callbackRegistry(callbackRegistry)
                {

                }

                !JavascriptAsyncObjectWrapper()
                {
                    _jsPropertyHandler = nullptr;
                }

                ~JavascriptAsyncObjectWrapper()
                {
                    this->!JavascriptAsyncObjectWrapper();

                    _callbackRegistry = nullptr;
                    _methodCallbackSave = nullptr;
                    for each (JavascriptAsyncMethodWrapper^ var in _wrappedMethods)
                    {
                        delete var;
                    }

                    for each (JavascriptAsyncPropertyWrapper^ var in _wrappedProperties)
                    {
                        delete var;
                    }
                }

                void Bind(JavascriptObject^ object, const CefRefPtr<CefV8Value> &value);
            };
        }
    }
}
