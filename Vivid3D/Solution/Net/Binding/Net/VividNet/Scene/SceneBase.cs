using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Scene.Nodes;

namespace VividNet.Scene
{
    public class SceneBase : VividObj
    {

        public SceneNode Root = null;

        public List<NodeLight> Lights;

        public SceneBase()
        {

            Lights = new List<NodeLight>();
            ID = BindScene.vNewScene();
            Root = new SceneNode();
            SetRoot(Root);



        }

        public NodeCam Cam
        {
            get
            {
                _Cam = new NodeCam(BindScene.vSceneGetCam(ID));
                return _Cam;
            }
            set
            {
                _Cam = Cam;
            }
        }
        public NodeCam _Cam;

        public void SetRoot(SceneNode node)
        {

            BindScene.vSceneSetRoot(ID, node.ID);
            Root = node;

        }

        public SceneNode AddNode(SceneNode node)
        {

            Root.AddNode(node);
            return null;
        }

        public NodeLight AddLight(NodeLight light)
        {
            BindScene.vSceneAddLight(ID, light.ID);
            Lights.Add(light);
            return light;
        }

    }
}
