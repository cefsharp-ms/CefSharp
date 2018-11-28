namespace CefSharp
{
    public interface IColorChooserCallback
    {
        void ChooseColor(uint color);

        void End();
    }
}
