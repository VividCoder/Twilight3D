using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Scene.Nodes;
using VividNet.Scene;
using VividNet.Math;

namespace VividNet.Module
{
    public class NodeModule : ModuleBase
    {

        public NodeEntity Entity
        {
            get;
            set;
        }

        public SceneNode Node
        {
            get;
            set;
        }

        public NodeModule()
        {

        }

        public void SetNode(SceneNode node)
        {

            Node = node;
            if(node is NodeEntity)
            {
                Entity = node as NodeEntity;
            }

        }

        public NodeModule(SceneNode node)
        {

            Node = node;

        }

        public NodeModule(NodeEntity entity)
        {

            Entity = entity;

        }


    }
}
