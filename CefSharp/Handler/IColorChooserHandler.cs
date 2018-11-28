namespace CefSharp
{
    public interface IColorChooserHandler
    {
        bool OnCreateColorSelection(IBrowser browser, uint defaultColor, IColorChooserCallback callback);

        void OnSelectedColor(IBrowser browser, uint color);

        void OnEndColorSelection(IBrowser browser);
    }
}
