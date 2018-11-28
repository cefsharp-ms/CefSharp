using System;

namespace CefSharp
{
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = false, Inherited = true)]
    public sealed class JavascriptBindingAttribute : Attribute
    {
        public bool FireAndForget { get; set; }

        public bool Sync { get; set; }

        public JavascriptBindingAttribute()
        {

        }

        public JavascriptBindingAttribute(bool fireAndForget)
        {
            FireAndForget = fireAndForget;
        }
    }
}
