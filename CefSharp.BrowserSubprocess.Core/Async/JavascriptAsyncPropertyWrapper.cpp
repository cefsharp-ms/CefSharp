
#include "stdafx.h"
#include "JavascriptCallbackRegistry.h"
#include "JavascriptAsyncPropertyWrapper.h"
#include "JavascriptAsyncObjectWrapper.h"

namespace CefSharp
{
    namespace Internals
    {
        namespace Async
        {
            void JavascriptAsyncPropertyWrapper::Bind(const CefRefPtr<CefV8Value>& value)
            {
                auto propertyName = StringUtils::ToNative(_prop->JavascriptName);
                auto clrPropertyName = _prop->JavascriptName;

                if (_prop->IsComplexType)
                {
                    auto javascriptObjectWrapper = gcnew JavascriptAsyncObjectWrapper(_callbackRegistry, _methodCallbackSave);
                    javascriptObjectWrapper->Bind(_prop->JsObject, value);

                    _javascriptObjectWrapper = javascriptObjectWrapper;
                }
                else
                {
                    auto propertyAttribute = _prop->IsReadOnly ? V8_PROPERTY_ATTRIBUTE_READONLY : V8_PROPERTY_ATTRIBUTE_NONE;

                    value->SetValue(propertyName, V8_ACCESS_CONTROL_DEFAULT, propertyAttribute);
                }
            }
        }
    }
}
