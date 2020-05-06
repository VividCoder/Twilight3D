using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindLight
    {

        [DllImport("VividBind.dll")]
        public static extern IntPtr vNewLight();

        [DllImport("VividBind.dll")]
        public static extern void vLightSetDiff(IntPtr l, float r, float g, float b);

    }
}
