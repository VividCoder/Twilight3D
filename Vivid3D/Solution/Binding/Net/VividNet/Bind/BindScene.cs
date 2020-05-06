using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
  
    class BindScene
    {

        [DllImport("VividBind.dll")]
        public static extern IntPtr vNewScene();

        [DllImport("VividBind.dll")]
        public static extern IntPtr vNewSceneNode();

        [DllImport("VividBind.dll")]
        public static extern void vSceneSetRoot(IntPtr scene, IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern void vSceneNodeAddNode(IntPtr node1, IntPtr node2);

        [DllImport("VividBind.dll")]
        public static extern int vSceneNodeNodeCount(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneNodeGetNode(IntPtr node, int num);

        [DllImport("VividBind.dll")]
        public static extern int vSceneNodeGetType(IntPtr node);

        public static string vNodeGetName(IntPtr node)
        {
            var p = _vSceneNodeGetName(node);
            return Marshal.PtrToStringAnsi(p);
        }

        [DllImport("VividBind.dll")]
        static extern IntPtr _vSceneNodeGetName(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern void vSceneNodeSetPos(IntPtr node, float x, float y, float z);

        [DllImport("VividBind.dll")]
        public static extern float vSceneNodeGetPosX(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern float vSceneNodeGetPosY(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern float vSceneNodeGetPosZ(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern void vSceneAddLight(IntPtr scene, IntPtr light);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneGetCam(IntPtr scene);





    }
}
