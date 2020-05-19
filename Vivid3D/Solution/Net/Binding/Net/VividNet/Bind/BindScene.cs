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
        public static extern float vSceneGetGlobalPosX(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern float vSceneGetGlobalPosY(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern float vSceneGetGlobalPosZ(IntPtr node);

        [DllImport("VividBind.dll")]
        public static extern void vSceneAddLight(IntPtr scene, IntPtr light);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneGetCam(IntPtr scene);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneNodeSetRotate(IntPtr node, float pitch, float yaw, float roll);

        [DllImport("VividBind.dll")]
        public static extern void vNodeMove(IntPtr node, float x, float y, float z);


        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneRayToTri(IntPtr scene, float ox, float oy, float oz, float vx, float vy, float vz);

        [DllImport("VividBind.dll")]
        public static extern float vSceneHitPX(IntPtr hit);

        [DllImport("VividBind.dll")]
        public static extern float vSceneHitPY(IntPtr hit);
        [DllImport("VividBind.dll")]
        public static extern float vSceneHitPZ(IntPtr hit);

        [DllImport("VividBind.dll")]
        public static extern int vSceneHitHit(IntPtr hit);

        [DllImport("VividBind.dll")]
        public static extern float vSceneHitDis(IntPtr hit);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneHitEntity(IntPtr hit);

        [DllImport("VividBind.dll")]
        public static extern IntPtr vSceneCamPick(IntPtr scene, int mx, int my);

        [DllImport("VividBind.dll",CharSet = CharSet.Ansi)]
        public extern static int vSceneNodeSetName(IntPtr node, [MarshalAs(UnmanagedType.LPStr)]string path);

        [DllImport("VividBind.dll", CharSet = CharSet.Ansi)]
        public extern static void vSceneNodeSetNameRC(IntPtr node, [MarshalAs(UnmanagedType.LPStr)]string path);

        [DllImport("VividBind.dll")]
        public extern static void vNodeRotateLocal(IntPtr node, float pitch, float yaw, float roll);

        [DllImport("VividBind.dll")]
        public extern static void vNodeRotateGlobal(IntPtr node, float pitch, float yaw, float roll);



    }

}
