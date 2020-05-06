using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindImport
    {

        [DllImport("VividBind.dll")]
        public static extern IntPtr vImportEntityAI([MarshalAs(UnmanagedType.LPStr)] string path);


    }

}
