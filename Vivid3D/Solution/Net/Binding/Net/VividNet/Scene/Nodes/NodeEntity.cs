using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Mesh;

namespace VividNet.Scene.Nodes
{
    public class NodeEntity : SceneNode
    {
        public NodeEntity(IntPtr id)
        {
            ID = id;
            Name = BindScene.vNodeGetName(ID);
            this.UpdateCS();
           

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
