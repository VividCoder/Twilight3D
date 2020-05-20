using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindDebug
    {

        [DllImport("VividBind.dll")]
        public extern static void vDebugScene(IntPtr p);

    }
}
