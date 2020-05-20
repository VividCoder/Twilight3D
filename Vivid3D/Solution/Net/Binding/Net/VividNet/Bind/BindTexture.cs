using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    public class BindTexture
    {

        [DllImport("VividBind.dll")]
        public extern static IntPtr vLoadTexture2D([MarshalAs(UnmanagedType.LPStr)]string path,int mp);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vCreateTexture2D([In, Out] [MarshalAs(UnmanagedType.LPArray)] byte[] data, int w, int h,int bpp);

        public static string vTextureGetPath(IntPtr node)
        {
            var p = _vTextureGetPath(node);
            return Marshal.PtrToStringAnsi(p);
        }

        [DllImport("VividBind.dll")]
        public extern static IntPtr _vTextureGetPath(IntPtr tex);
    }
}
