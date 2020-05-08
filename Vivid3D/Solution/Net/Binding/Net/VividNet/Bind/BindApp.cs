using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindApp
    {

        [DllImport("VividBind.dll")]
        public static extern void vAppSetSize(int w, int h);

    }
}
