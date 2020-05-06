using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Math;

namespace VividNet.Scene.Nodes
{
    public class SceneNode : VividObj
    {

        public List<SceneNode> Nodes = new List<SceneNode>();
        public SceneNode Root
        {
            get;
            set;

        }

        public float3 Position
        {
            get
            {
                return _Pos;
            }
            set
            {
                _Pos = value;
                BindScene.vSceneNodeSetPos(ID, value.X, value.Y, value.Z);
            }
        }
        public float3 _Pos;


        public string Name
        {
            get;
            set;
        }

      

        public SceneNode(IntPtr id)
        {
            _Pos = new float3(0, 0, 0);
            ID = id;
            BindScene.vNodeGetName(ID);
            GetCPos();
            UpdateCS();

        }
        public SceneNode()
        {
         
            ID = BindScene.vNewSceneNode();
            _Pos = new float3(0, 0, 0);
        }

        public SceneNode AddNode(SceneNode node)
        {

            Nodes.Add(node);
            BindScene.vSceneNodeAddNode(ID, node.ID);
            return node;
        }

        private void GetCPos()
        {

            _Pos = new float3(BindScene.vSceneNodeGetPosX(ID), BindScene.vSceneNodeGetPosY(ID), BindScene.vSceneNodeGetPosZ(ID));

        }

        //public NodeCam GetCam()
       // {
         //   return Cam;
        //}


        public void UpdateCS()
        {

            Nodes.Clear();
            int nc = BindScene.vSceneNodeNodeCount(ID);

            for(int i=0;i<nc;i++)
            {

                IntPtr cn = BindScene.vSceneNodeGetNode(ID, i);
                int nt = BindScene.vSceneNodeGetType(cn);
                if(nt == 1)
                {
                    var nn = new SceneNode(cn);
                    Nodes.Add(nn);
                    nn.Root = this;
                }
                if(nt == 2)
                {
                    var nn = new NodeEntity(cn);
                    Nodes.Add(nn);
                    nn.Root = this;
                }
                if(nt == 0)
                {
                    int why = 1;

                }
            }

        }

    }
}
