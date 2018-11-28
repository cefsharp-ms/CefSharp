using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CefSharp.WinForms.Example.Handlers
{
    public class ColorChooserHandler : IColorChooserHandler
    {
        private readonly Control control;

        public ColorChooserHandler(Control control)
        {
            this.control = control;
        }

        public bool OnCreateColorSelection(IBrowser browser, uint defaultColor, IColorChooserCallback callback)
        {
            control.BeginInvoke(new Action(() =>
            {
                var dialog = new ColorDialog();
                dialog.Color = UIntToColor(defaultColor);
                var dialogResult = dialog.ShowDialog();
                if (dialogResult == DialogResult.OK)
                {
                    callback.ChooseColor(ColorToUInt(dialog.Color));
                }

                callback.End();
            }));


            return true;
        }

        public void OnEndColorSelection(IBrowser browser)
        {
            
        }

        public void OnSelectedColor(IBrowser browser, uint color)
        {

        }

        private uint ColorToUInt(Color color)
        {
            return (uint)((color.A << 24) | (color.R << 16) |
                          (color.G << 8) | (color.B << 0));
        }

        private Color UIntToColor(uint color)
        {
            byte a = (byte)(color >> 24);
            byte r = (byte)(color >> 16);
            byte g = (byte)(color >> 8);
            byte b = (byte)(color >> 0);
            return Color.FromArgb(a, r, g, b);
        }
    }
}
