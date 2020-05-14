using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindEntity
    {

        [DllImport("VividBind.dll")]
        public static extern IntPtr vNewEntity();

        [DllImport("VividBind.dll")]
        public static extern void vEntityAddMesh(IntPtr ent, IntPtr mesh);

        [DllImport("VividBind.dll")]
        public static extern void vEntitySetRenderMode(IntPtr ent, int rMode);

    }
}
