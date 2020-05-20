using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Material;
using VividNet.Math;
using VividNet.Scene.Nodes;
using VividNet.Texture;

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

        public Mesh3D(IntPtr mesh)
        {

            ID = mesh;

        }

        public Material.MaterialBase GetMat()
        {

            return new Material.MaterialBase(BindMesh.vMeshGetMat(ID));

        }

        public void SetMaterial(MaterialBase mat)
        {

            BindMesh.vMeshSetMat(ID,mat.ID);

        }

        public void GetBounds(NodeEntity node)
        {

            IntPtr r = BindMesh.vMeshGetBounds(node.ID,ID);


        }

        public void SetVertex(int ix,Vertex3D vertex)
        {

            BindMesh.vSetMeshVertex(ID, ix, vertex.pos.X, vertex.pos.Y, vertex.pos.Z, vertex.uv.X, vertex.uv.Y, vertex.uv.Z, vertex.norm.X, vertex.norm.Y, vertex.norm.Z, vertex.tan.X, vertex.tan.Y, vertex.tan.Z, vertex.binorm.X, vertex.binorm.Y, vertex.binorm.Z);

        }

        public void SetTri(int ix, Tri tri)
        {

            BindMesh.vSetMeshTri(ID, ix, tri.V0, tri.V1, tri.V2);

        }

        public int GetTriCount()
        {

            return BindMesh.vMeshGetTriCount(ID);

        }

        public Tri GetTri(int ix)
        {
            int[] dat = new int[3];
            IntPtr id = BindMesh.vMeshGetTri(ID,ix);
            BindMesh.vMeshTriData(id, dat);
            return new Tri(dat[0], dat[1], dat[2]);
        }

        public Vertex3D GetVertex(int ix)
        {
            float[] dat = new float[16];
            IntPtr id = BindMesh.vMeshGetVertex(ID, ix);
            BindMesh.vMeshVertexData(id, dat);
            float3 pos = new float3(dat[0], dat[1], dat[2]);
            float3 uv = new float3(dat[3],dat[4],dat[5]);
            float3 norm = new float3(dat[6], dat[7], dat[8]);
            float3 tan = new float3(dat[9], dat[10], dat[11]);
            float3 bi = new float3(dat[12], dat[13], dat[14]);

            Vertex3D v = new Vertex3D(pos);
            v.uv = uv;
            v.norm = norm;
            v.tan = tan;
            v.binorm = bi;

            return v;



        }

        

        public int GetVertexCount()
        {

            return BindMesh.vMeshGetVertexCount(ID);

        }

        public void Final()
        {

            BindMesh.vMeshFinal(ID);

        }

    }
}
