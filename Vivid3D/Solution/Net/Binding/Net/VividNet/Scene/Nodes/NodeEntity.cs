using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Material;
using VividNet.Mesh;
using VividNet.Texture;

namespace VividNet.Scene.Nodes
{
    public class NodeEntity : SceneNode
    {
        public NodeEntity(IntPtr id)
        {
            ID = id;
           // Name = BindScene.vNodeGetName(ID);
            Console.WriteLine("Set:");
            this.UpdateCS();
           

        }

        
        public override void WriteNode(BinaryWriter w)
        {
            if (NoSave)
            {
               w.Write(0);
                return;
            }
            w.Write((int)2);

            WriteVec3(Position, w);
            //WriteVec3(Scale,w);

            WriteRotation(w);
         

            w.Write(MeshCount());
            for(int i = 0; i < MeshCount(); i++)
            {
                var m = GetMesh(i);

                int vc = m.GetVertexCount();
                int tc = m.GetTriCount();

                w.Write(vc);
                w.Write(tc);
                for (int v = 0; v < vc; v++)
                {

                    Vertex3D vd = m.GetVertex(v);

                    WriteVec3(vd.pos,w);
                    WriteVec3(vd.uv,w);
                    WriteVec3(vd.norm, w);
                    WriteVec3(vd.tan, w);
                    WriteVec3(vd.binorm, w);

                }

               

                for(int t = 0; t < tc; t++)
                {

                    Tri tr = m.GetTri(t);

                    w.Write(tr.V0);
                    w.Write(tr.V1);
                    w.Write(tr.V2);


                }

                var mat = m.GetMat();

                var dif = mat.GetDiffuse();
                var norm = mat.GetNormal();

                w.Write(dif.GetPath());
                w.Write(norm.GetPath());

                Console.WriteLine("Dif:" + dif.GetPath());
                Console.WriteLine("Norm:" + norm.GetPath());
              //  Console.WriteLine("VC:" + vc + " TC:" + tc);
               
                
            }

            w.Write(Nodes.Count);

            foreach (var n in Nodes)
            {
                n.WriteNode(w);
            }
        }
        public override void ReadNodeData(BinaryReader r)
        {
            //    base.ReadNodeData(r);
            Position = ReadVec3(r);
            ReadRotation(r);
            int mc = r.ReadInt32();
            for(int i = 0; i < mc; i++)
            {

                
                int vc = r.ReadInt32();
                int tc = r.ReadInt32();

                var mesh = new Mesh3D(vc, tc);

                for(int v = 0; v < vc; v++)
                {
                    Math.float3 pos = ReadVec3(r);

                    Vertex3D vd = new Vertex3D(pos);
                    vd.uv = ReadVec3(r);
                    vd.norm = ReadVec3(r);
                    vd.tan = ReadVec3(r);
                    vd.binorm = ReadVec3(r);

                    mesh.SetVertex(v, vd);

                }

                for(int t = 0; t < tc; t++)
                {

                    var tr = new Tri(0, 0, 0);

                    tr.V0 = r.ReadInt32();
                    tr.V1 = r.ReadInt32();
                    tr.V2 = r.ReadInt32();

                    mesh.SetTri(t, tr);


                }

                var mat = new MaterialBase();

                mat.SetDiffuse(Texture2D.QuickLoad(r.ReadString()));
                mat.SetNormal(Texture2D.QuickLoad(r.ReadString()));

                mesh.SetMaterial(mat);

                mesh.Final();

                AddMesh(mesh);

            }

            int nc = r.ReadInt32();
            for (int i = 0; i < nc; i++)
            {

                var nn = SceneNode.ReadNode(r);
                if (nn != null)
                {
                    AddNode(nn);
                }

            }

        }
        public NodeEntity()
        {

            ID = BindEntity.vNewEntity();

        }

        public int MeshCount()
        {

            return BindEntity.vEntityMeshCount(ID);

        }

        public Mesh3D GetMesh(int i)
        {

            return new Mesh3D(BindEntity.vEntityGetMesh(ID, i));

        }

        public void SetMaterialRc(Material.MaterialBase mat)
        {

            for(int i = 0; i < MeshCount(); i++)
            {

                var mesh = GetMesh(i);

                mesh.SetMaterial(mat);

            }

            foreach(var node in Nodes)
            {

                var ent = node as NodeEntity;

                ent.SetMaterialRc(mat);

            }

        }

        public void AddMesh(Mesh3D mesh)
        {

            BindEntity.vEntityAddMesh(ID, mesh.ID);

        }

        public void SetRenderMode(RenderMode mode)
        {

            BindEntity.vEntitySetRenderMode(ID, (int)mode);
            foreach(var e in Nodes)
            {

                if(e is NodeEntity)
                {

                    var ee = e as NodeEntity;
                    ee.SetRenderMode(mode);


                }

            }

        }

        public void SetDoRender(bool render)
        {

            BindEntity.vEntitySetDoRender(ID, render ? 1 : 0);

        }

        public bool GetDoRender()
        {

            return BindEntity.vEntityGetDoRender(ID) == 1;

        }
        public void SetCanPick(bool pick)
        {

            if (pick)
            {
                BindEntity.vSetCanPick(ID, 1);
            }
            else
            {
                BindEntity.vSetCanPick(ID, 0);
            }

        }

        public bool CanPick()
        {

            if (BindEntity.vCanPick(ID)==1)
            {
                return true;
            }
            return false;

        }

    }
    public enum RenderMode
    {

        Lit=0,FullBright

    }
}
