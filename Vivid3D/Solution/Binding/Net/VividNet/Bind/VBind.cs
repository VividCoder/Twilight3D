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

        [DllImport("VividBind.dll",CallingConvention = CallingConvention.ThisCall)]
        public static extern int testBind(int v);

    }
}
