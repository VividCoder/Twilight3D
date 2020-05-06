using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    public class BindDraw2D
    {
        [DllImport("VividBind.dll")]
        public static extern IntPtr vNewDraw2D();

        [DllImport("VividBind.dll")]
        public static extern void vDraw2D_Rect(IntPtr d2d,int x,int y, int w,int h);

        [DllImport("VividBind.dll")]
        public static extern void vDraw2D_SetTexture(IntPtr d2d, IntPtr tex);

        [DllImport("VividBind.dll")]
        public static extern void vDraw2D_Bind(IntPtr d2d);

    }
}
