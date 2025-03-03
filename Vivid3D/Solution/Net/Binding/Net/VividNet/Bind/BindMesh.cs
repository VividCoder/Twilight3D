﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Bind
{
    class BindMesh
    {

        [DllImport("VividBind.dll")]
        public extern static IntPtr vNewMesh(int vertices, int tris);

        [DllImport("VividBind.dll")]
        public extern static void vSetMeshVertex(IntPtr mesh, int ix, float x1, float y1, float z1, float u, float v, float w, float nx, float ny, float nz, float tx, float ty, float tz, float bx, float by, float bz);

        [DllImport("VividBind.dll")]
        public extern static void vSetMeshTri(IntPtr mesh, int ix, int v0, int v1, int v2);

        [DllImport("VividBind.dll")]
        public extern static void vMeshFinal(IntPtr mesh);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vMeshGetMat(IntPtr mesh);

        [DllImport("VividBind.dll")]
        public extern static void vMeshSetMat(IntPtr mesh, IntPtr mat);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vMeshGetBounds(IntPtr ent,IntPtr mesh);

        [DllImport("VividBind.dll")]
        public extern static int vMeshGetTriCount(IntPtr mesh);

        [DllImport("VividBind.dll")]
        public extern static int vMeshGetVertexCount(IntPtr mesh);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vMeshGetVertex(IntPtr mesh, int ix);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vMeshGetTri(IntPtr mesh, int ix);

        [DllImport("VividBind.dll")]
        public extern static void vMeshTriData(IntPtr node, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] int[] arr);

        [DllImport("VividBind.dll")]
        public extern static void vMeshVertexData(IntPtr node, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] float[] arr);





    }
}
