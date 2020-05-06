using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;

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

        }


    }
}
