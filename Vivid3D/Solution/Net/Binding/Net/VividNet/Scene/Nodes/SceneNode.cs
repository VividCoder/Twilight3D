using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Math;
using VividNet.Module;

namespace VividNet.Scene.Nodes
{
    public class SceneNode : VividObj
    {

        public static List<SceneNode> AllNodes = new List<SceneNode>();

        public static SceneNode GetNode(IntPtr node,bool entity)
        {

            foreach(var n in AllNodes)
            {
                if(n.ID == node)
                {
                    return n;
                }
            }

            if (entity)
            {
                var nn = new NodeEntity(node);
                AllNodes.Add(nn);
                nn.UpdateCS();
                return nn;
            }
            else
            {
                var nn = new SceneNode(node);
                AllNodes.Add(nn);
                nn.UpdateCS();
                return nn;
            }



        }

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
                _Pos = new float3(BindScene.vSceneNodeGetPosX(ID), BindScene.vSceneNodeGetPosY(ID), BindScene.vSceneNodeGetPosZ(ID));
                return _Pos;
            }
            set
            {
                _Pos = value;
                BindScene.vSceneNodeSetPos(ID, value.X, value.Y, value.Z);
            }
        }
        public float3 _Pos;

        public List<NodeModule> Modules
        {
            get;
            set;
        }

        public float3 GetGlobalPos()
        {

            return new float3(BindScene.vSceneGetGlobalPosX(ID), BindScene.vSceneGetGlobalPosY(ID), BindScene.vSceneGetGlobalPosZ(ID));

        }

        public List<ModuleLink> ModLinks = new List<ModuleLink>();

        public void AddModuleLink(ModuleLink link)
        {
            ModLinks.Add(link);
        }
        public void UpdateScripts()
        {
            foreach(var mod in Modules)
            {

                mod.UpdateModule();

            }

        }
        public void LoadScripts()
        {

            foreach(var link in ModLinks)
            {

                Console.WriteLine("Compiling script:" + link.CodePath);
                string stext = System.IO.File.ReadAllText(link.CodePath);
                dynamic sc = CSScriptLibrary.CSScript.LoadCode(stext).CreateObject("*");

                
                Modules.Add(sc);
                sc.SetNode(this);
                sc.InitModule();
                Console.WriteLine("Compiled and Added module.");


               // Modules.Add(new ModuleBase(link.CodePath));

            }

        }

        public string Name
        {
            get
            {
                return BindScene.vNodeGetName(ID);
            }
            set
            {
                BindScene.vSceneNodeSetName(ID, value);
            }
        }

      
        public void TurnLocal(float pitch,float yaw,float roll)
        {

            BindScene.vNodeRotateLocal(ID, pitch, yaw, roll);

        }

        public void TurnGlobal(float pitch,float yaw,float roll)
        {
            BindScene.vNodeRotateGlobal(ID, pitch, yaw, roll);
        }

        public void SetNameRC(string name)
        {

            BindScene.vSceneNodeSetNameRC(ID, name);

        }

        public SceneNode(IntPtr id)
        {
            Modules = new List<NodeModule>();
            _Pos = new float3(0, 0, 0);
            ID = id;
            Name = BindScene.vNodeGetName(ID);
            NotEdit = false;
            GetCPos();
            UpdateCS();

        }
        public SceneNode()
        {
            Modules = new List<NodeModule>();
            ID = BindScene.vNewSceneNode();
            _Pos = new float3(0, 0, 0);
            NotEdit = false;
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

        public bool NotEdit
        {
            get;
            set;
        }

        public void SetRotation(float pitch,float yaw,float roll)
        {

           // pitch = Math.Maths.DegToRad(pitch);
         //   yaw = Math.Maths.DegToRad(yaw);
          //  roll = Math.Maths.DegToRad(roll);
            BindScene.vSceneNodeSetRotate(ID, pitch, yaw, roll);

        }

        public void Move(float x,float y,float z)
        {

            BindScene.vNodeMove(ID, x, y, z);

        }

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
                    var nn = GetNode(cn, false);//   //new SceneNode(cn);
                    Nodes.Add(nn);
                    nn.Root = this;
                }
                if(nt == 2)
                {
                    var nn = GetNode(cn, true);
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
