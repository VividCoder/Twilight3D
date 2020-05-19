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

        [DllImport("VividBind.dll")]
        public static extern int vEntityMeshCount(IntPtr ent);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vEntityGetMesh(IntPtr ent,int i);

        [DllImport("VividBind.dll")]
        public static extern void vSetCanPick(IntPtr ent, int can);

        [DllImport("VividBind.dll")]
        public static extern int vCanPick(IntPtr ent);

        [DllImport("VividBind.dll")]
        public static extern void vEntitySetDoRender(IntPtr ent, int render);

        [DllImport("VividBind.dll")]
        public static extern int vEntityGetDoRender(IntPtr ent);


    }


}
