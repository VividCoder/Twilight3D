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
        public static SceneNode ReadNode(BinaryReader r)
        {
            SceneNode res = null;
            int typ = r.ReadInt32();
            switch (typ)
            {
                case 0:

                   return null;
                case 1:
                    res = new SceneNode();
                    break;
                case 2:
                    res = new NodeEntity();
                    break;

            }

            res.ReadNodeData(r);

            return res;
        }

        public virtual void ReadNodeData(BinaryReader r)
        {
            Position = ReadVec3(r);

            ReadRotation(r);
            int nc = r.ReadInt32();
            for(int i = 0; i < nc; i++)
            {

                var nn = SceneNode.ReadNode(r);
                
                if (nn != null)
                {
                    AddNode(nn);
                    //nn.Root = this;
                    //Nodes.Add(nn);

                }

            }
        }
        public virtual void WriteNode(BinaryWriter w)
        {
            if (NoSave)
            {
                w.Write(0);
                return;
            }
          //  if (this is SceneNode)
        //    {
                w.Write((int)1);
        
            WriteVec3(Position,w);
            //WriteVec3(Scale,w);

            WriteRotation(w);
            w.Write(Nodes.Count);
            foreach(var n in Nodes)
            {
                n.WriteNode(w);
            }

        }

        public void WriteVec3(float3 vec, BinaryWriter w)
        {

            w.Write(vec.X);
            w.Write(vec.Y);
            w.Write(vec.Z);

        }

        public float3 ReadVec3(BinaryReader r)
        {

            return new float3(r.ReadSingle(), r.ReadSingle(), r.ReadSingle());

        }

        public void WriteRotation(BinaryWriter w)
        {

            float[] arr = new float[16];

            BindScene.vNodeGetRotation(ID, arr);

            for (int i = 0; i < 16; i++)
            {
                w.Write(arr[i]);
            }
        
        }

        public void ReadRotation(BinaryReader r)
        {

            float[] mat = new float[16];
            for(int i = 0; i < 16; i++)
            {
                mat[i] = r.ReadSingle();
            }
            BindScene.vNodeSetRotation(ID, mat);

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
            NoSave = false;

        }
        public SceneNode()
        {
            Modules = new List<NodeModule>();
            ID = BindScene.vNewSceneNode();
            _Pos = new float3(0, 0, 0);
            NotEdit = false;
            NoSave = false;
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

        public bool NoSave
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
