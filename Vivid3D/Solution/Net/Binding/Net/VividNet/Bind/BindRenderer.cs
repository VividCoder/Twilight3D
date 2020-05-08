using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindRenderer
    {

        [DllImport("VividBind.dll")]
        public static extern IntPtr vNewRenderer(IntPtr scene);

        [DllImport("VividBind.dll")]
        public static extern void vRendererRender(IntPtr ren);

    }
}
