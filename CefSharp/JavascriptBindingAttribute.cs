using System;

namespace CefSharp
{
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = false, Inherited = true)]
    public sealed class JavascriptBindingAttribute : Attribute
    {
        public bool FireAndForget { get; }

        public JavascriptBindingAttribute(bool fireAndForget)
        {
            FireAndForget = fireAndForget;
        }
    }
}
