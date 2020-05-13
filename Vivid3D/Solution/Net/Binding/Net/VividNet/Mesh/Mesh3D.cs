using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Math;

namespace VividNet.Mesh
{

    public class Vertex3D
    {

        public float3 pos;
        public float3 uv;
        public float3 norm;
        public float3 tan;
        public float3 binorm;
        public Vertex3D(float3 p)
        {

            pos = p;


        }

    }

    public class Tri
    {
        public int V0, V1, V2;
        public Tri(int v0,int v1,int v2)
        {

            V0 = v0;
            V1 = v1;
            V2 = v2;

        }
    }

    public class Mesh3D : VividObj
    {

        public Mesh3D(int vertices,int indices)
        {

            ID = BindMesh.vNewMesh(vertices, indices);

        }

        public void SetVertex(int ix,Vertex3D vertex)
        {

            BindMesh.vSetMeshVertex(ID, ix, vertex.pos.X, vertex.pos.Y, vertex.pos.Z, vertex.uv.X, vertex.uv.Y, vertex.uv.Z, vertex.norm.X, vertex.norm.Y, vertex.norm.Z, vertex.tan.X, vertex.tan.Y, vertex.tan.Z, vertex.binorm.X, vertex.binorm.Y, vertex.binorm.Z);

        }

        public void SetTri(int ix, Tri tri)
        {

            BindMesh.vSetMeshTri(ID, ix, tri.V0, tri.V1, tri.V2);

        }

        public void Final()
        {

            BindMesh.vMeshFinal(ID);

        }

    }
}
