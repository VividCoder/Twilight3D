using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Math;
using VividNet.Mesh;
using VividNet.Scene.Nodes;

namespace VividNet.Scene
{

    public class SceneHit
    {
        public float3 Pos;
        public bool Hit;
        public float Dis;
        public NodeEntity Node;
        public Mesh3D Mesh;
    }
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

        public SceneHit CamPick(int mx,int my)
        {

            IntPtr hit = BindScene.vSceneCamPick(ID,mx, my);
            var sh = new SceneHit();

            sh.Pos = new float3(BindScene.vSceneHitPX(hit), BindScene.vSceneHitPY(hit), BindScene.vSceneHitPZ(hit));
            sh.Dis = BindScene.vSceneHitDis(hit);
            var hh = BindScene.vSceneHitHit(hit);

            if (hh == 1)
            {
                sh.Hit = true;
            }
            else
            {
                sh.Hit = false;
            }

            return sh;
        }

        public SceneHit RayToTri(float3 origin,float3 vec)
        {

            IntPtr hit =  BindScene.vSceneRayToTri(ID, origin.X, origin.Y, origin.Z, vec.X, vec.Y, vec.Z);

            var sh = new SceneHit();

            sh.Pos =new float3(BindScene.vSceneHitPX(hit), BindScene.vSceneHitPY(hit), BindScene.vSceneHitPZ(hit));
            sh.Dis = BindScene.vSceneHitDis(hit);
            var hh = BindScene.vSceneHitHit(hit);

            if (hh == 1)
            {
                sh.Hit = true;
            }
            else
            {
                sh.Hit = false;
            }

            return sh;
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
