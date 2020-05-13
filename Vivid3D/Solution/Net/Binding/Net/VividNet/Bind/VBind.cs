using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace VividNet.Bind
{
    public class VBind
    {

        [DllImport("VividBind.dll")]
        public static extern int testBind(int v);

        [DllImport("VividBind.dll")]
        public static extern int initWinHW(IntPtr hw);

        [DllImport("VividBind.dll")]
        public extern static int vRender();

        [DllImport("VividBind.dll")]
        public extern static int vPresent();

        [DllImport("VividBind.dll")]
        public extern static int vSetPath([MarshalAs(UnmanagedType.LPStr)]string path);

        [DllImport("VividBind.dll")]
        public extern static int vSetImpPath([MarshalAs(UnmanagedType.LPStr)]string path);

    }
}
