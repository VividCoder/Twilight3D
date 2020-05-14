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

        public void AddMesh(Mesh3D mesh)
        {

            BindEntity.vEntityAddMesh(ID, mesh.ID);

        }

        public void SetRenderMode(RenderMode mode)
        {

            BindEntity.vEntitySetRenderMode(ID, (int)mode);

        }

    }
    public enum RenderMode
    {

        Lit=0,FullBright

    }
}
