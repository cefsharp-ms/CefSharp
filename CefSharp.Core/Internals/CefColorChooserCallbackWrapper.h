#pragma once

#include "Stdafx.h"

#include "include\cef_color_chooser_handler.h"
#include "CefWrapper.h"

namespace CefSharp
{
    namespace Internals
    {
        private ref class CefColorChooserCallbackWrapper : public IColorChooserCallback, public CefWrapper
        {
        private:
            MCefRefPtr<CefColorChooserCallback> _callback;

        public:
            CefColorChooserCallbackWrapper(CefRefPtr<CefColorChooserCallback> &callback)
                : _callback(callback)
            {

            }

            !CefColorChooserCallbackWrapper()
            {
                _callback = NULL;
            }

            ~CefColorChooserCallbackWrapper()
            {
                this->!CefColorChooserCallbackWrapper();

                _disposed = true;
            }

            virtual void ChooseColor(unsigned int color)
            {
                ThrowIfDisposed();

                _callback->ChooseColor(color);
            }

            virtual void End()
            {
                _callback->End();
            }
        };
    }
}
