using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using VividNet;
using System.Configuration;
using System.Threading;
using VividNet.Texture;
using VividNet.Scene.Nodes;
using VividNet.Math;

namespace VividSceneEditor
{
    public partial class Viewer : DockContent
    {
        public static VividNet.Scene.Nodes.NodeCam Cam = null;
        public static VividNet.Renderer.SceneRenderer Renderer = null;
        public static VividNet.Scene.SceneBase Scene = null;
        public static VividNet.Scene.Nodes.NodeLight Light1;
        public static VividNet.Scene.Nodes.NodeEntity Grid1;
        public static VividNet.Scene.Nodes.NodeEntity GizmoTranslate;
        public static VividNet.Scene.Nodes.NodeEntity SelectedEntity;
        public static bool DragX, DragY, DragZ;
        public static EditMode EMode;
        public static SpaceMode SMode;
       // public static VividNet

        public Viewer()
        {
            DragX = DragY = DragZ = false;
            InitializeComponent();
            Text = "View";
            CT1 = new Thread(new ThreadStart(Control_Thread));
            CT1.Priority = ThreadPriority.Normal;
            CT1.Start();
            SetEditMode(EditMode.Translate);
            SetSpaceMode(SpaceMode.Global);
        }
        Thread CT1;
        int c = 0;
        public void Control_Thread()
        {

            while (true)
            {
                c = c + 1;
               // Console.WriteLine("!" + c);
                if (mF)
                {

                    Cam.Move(0, 0, 1);

                }
                if (mB)
                {
                    Cam.Move(0, 0, -1);
                }
                if (mL)
                {
                    Cam.Move(-1, 0, 0);
                }
                if (mR)
                {
                    Cam.Move(1, 0, 0);
                }
                System.Threading.Thread.Sleep(25);

            }

        }
        NodeEntity ge;
        protected override void OnLoad(EventArgs e)
        {


            VividApp.InitDisplay(this.Handle);
            VividNet.Bind.VBind.vSetPath(Environment.CurrentDirectory + "\\");
            Scene = new VividNet.Scene.SceneBase();
            Renderer = new VividNet.Renderer.SceneRenderer(Scene);
            Cam = Scene.Cam;
            Light1 = new VividNet.Scene.Nodes.NodeLight();
            Scene.AddLight(Light1);

            Light1.Position = new VividNet.Math.float3(0, 5, -5);
            Cam.Position = new VividNet.Math.float3(0, 35,0 );
            Grid1 = VividNet.Gen.GenGrid.Grid(50);
            Grid1.SetCanPick(false);
            Scene.AddNode(Grid1);
            Grid1.SetRenderMode(VividNet.Scene.Nodes.RenderMode.FullBright);
            //Grid1.SetRotation(90, 0, 0);

            Grid1.Position = new VividNet.Math.float3(0, 0,0);
            //base.OnLoad(e);
            GizmoTranslate = VividNet.Import.Importer.ImportEntityAI("edit/mesh/gizmo/drag2.obj");
            var gizmo_up = VividNet.Import.Importer.ImportEntityAI("edit/mesh/gizmo/drag2.obj");
            var gizmo_for = VividNet.Import.Importer.ImportEntityAI("edit/mesh/gizmo/drag2.obj");
            var gizmo_hit = VividNet.Import.Importer.ImportEntityAI("edit/mesh/gizmo/hit1.obj");
            ge = gizmo_hit;
            var m = new VividNet.Material.MaterialBase();
            var m2 = new VividNet.Material.MaterialBase();
            var m3 = new VividNet.Material.MaterialBase();

            var tex = new Texture2D("green.png");
            var tex2 = new Texture2D("orange.png");
            var tex3 = new Texture2D("blue.png");

            m.SetDiffuse(tex);
            m2.SetDiffuse(tex2);
            m3.SetDiffuse(tex3);

            gizmo_for.SetMaterialRc(m3);
            gizmo_up.SetMaterialRc(m2);
            gizmo_hit.SetMaterialRc(m3);
            GizmoTranslate.SetMaterialRc(m);
            GizmoTranslate.SetRotation(90, 0, 0);
            GizmoTranslate.SetNameRC("Giz:LeftRight");
           GizmoTranslate.AddNode(gizmo_up);
            gizmo_up.SetNameRC("Giz:UpDown");
           gizmo_for.SetNameRC("Giz:BackFor");
            GizmoTranslate.AddNode(gizmo_for);
            gizmo_up.SetRotation(90, 90, 0);
            gizmo_for.SetRotation(0, 0,-90);


            GizmoTranslate.SetRenderMode(VividNet.Scene.Nodes.RenderMode.FullBright);
            GizmoTranslate.SetDoRender(false);
            Scene.AddNode(GizmoTranslate);
            Scene.AddNode(gizmo_hit);

            //GizmoTranslate.SetCanPick(false);


           // var hit = Scene.RayToTri(new float3(0,3, -25), new float3(0, 0,1));
           // gizmo_hit.Position = hit.Pos;
            gizmo_hit.SetCanPick(false);

            // Console.WriteLine("PX:" + hit.Pos.X + " PY:" + hit.Pos.Y + " PZ:" + hit.Pos.Z + " Dis:" + hit.Dis + " Hit?:" + hit.Hit);
            //while (true)
            // {

            //}
            ContextMenuStrip  = contextMenuStrip1;
            Invalidate();
        }
        int x = 0;

        public void CheckBB(NodeEntity node)
        {

            for(int i = 0; i < node.MeshCount(); i++)
            {

                var msh = node.GetMesh(i);
                msh.GetBounds(node);


            }

            for(int i = 0; i < node.Nodes.Count; i++)
            {

                CheckBB((NodeEntity)node.Nodes[i]);

            }

        }

        int h = 0;
        private void Viewer_Paint(object sender, PaintEventArgs e)
        {
            VividApp.SetSize(Width, Height);

            x = x + 1;
            // Scene.Root.SetRotation(x*3, x, 0);

            VividNet.Bind.VBind.vRender();

            Renderer.Render();

            VividNet.Bind.VBind.vPresent();
            Invalidate();

           // var hit = Scene.CamPick(Width / 2, Height / 2);
            //if (hit.Hit)
            {
              //  Environment.Exit(1);
              //  ge.Position = hit.Pos;
                h++;
                //Console.WriteLine("P:" + ge.Position.X + " Y:" + ge.Position.Y + " Z:" + ge.Position.Z);
                //Console.WriteLine("Hit:" + h);

            }
            //else
            {
             //   Console.WriteLine("No Hit:" + h);
            }

            timer2.Enabled = true;
          
        }

        private void kryptonPanel1_Paint(object sender, PaintEventArgs e)
        {

        
        }

        private void Viewer_Load(object sender, EventArgs e)
        {

        }
        bool firstMove = true;
        int lx, ly;
        float cp, cy;
        bool camRot = false;

        private void Viewer_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Middle)
            {

                camRot = false;

            }
            if(e.Button == MouseButtons.Left)
            {
                DragX = DragY = DragZ = false;
            }
        }

        bool mF, mB, mL, mR;

        private void timer2_Tick(object sender, EventArgs e)
        {
            int vv = 5;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
        }

        private void translateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetEditMode(EditMode.Translate);
        }

        private void rotateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetEditMode(EditMode.Rotate);
        }

        private void globalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetSpaceMode(SpaceMode.Global);
        }

        private void localToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SetSpaceMode(SpaceMode.Local);
        }

        private void Viewer_KeyUp(object sender, KeyEventArgs e)
        {
            Console.WriteLine("E:" + e.KeyCode);
            switch (e.KeyCode)
            {
                case Keys.W:
                    mF = false;
                    break;
                case Keys.S:
                    mB = false;
                    break;
                case Keys.A:
                    mL = false; ;
                    break;
                case Keys.D:
                    mR = false;
                    break;
            }
        }

        private void Viewer_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.W:
                    mF = true;
                    break;
                case Keys.S:
                    mB = true;
                    break;
                case Keys.A:
                    mL = true;
                    break;
                case Keys.D:
                    mR = true;
                    break;
            }
        }



        public void SetEditMode(EditMode mode)
        {

            EMode = mode;
            //switch(EMode)
            //{
            //  case EditMode.Translate:
            //statusStrip1.Text = "Edit Mode:"+"Translate"



            //            }
            updateStatus();
        }
        public void SetSpaceMode(SpaceMode mode)
        {
            SMode = mode;
            updateStatus();
        }
        public void updateStatus()
        {

            toolLab1.Text = "Edit Mode:" + EMode.ToString() + " Space Mode:" + SMode.ToString();
            toolLab1.Invalidate();
            statusStrip1.Invalidate();
        }

        private void Viewer_MouseDown(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Middle)
            {
                camRot = true;
            }
            if(e.Button == MouseButtons.Left)
            {
                int mx, my;

                mx = lx;
                my = ly;
                my = Height - my;

                var hit = Scene.CamPick(mx, my);
                if (hit.Hit)
                {
                    Console.WriteLine("Hit:Yes");
                    string s = (hit.Node != null).ToString();
                    Console.WriteLine("Node?:" + s);
                    Console.WriteLine("NodeName:" + hit.Node.Name);

                }
            //    ge.Position = hit.Pos;

                if(hit.Node != null)
                {

                    //hit.Node.Name = "Test\n\0";

                    if (!hit.Node.Name.Contains("Giz:"))
                    {
                        SelectedEntity = hit.Node;
                        GizmoTranslate.SetDoRender(true);
                        GizmoTranslate.Position = hit.Node.GetGlobalPos();
                        Form1.Graph3D.SelectNode(hit.Node);
                        //   ge.Position = new float3(hit.Node.GetGlobalPos().X, hit.Node.GetGlobalPos().Y+6, hit.Node.GetGlobalPos().Z);
                    }
                    else
                    {

                        if(hit.Node.Name.Contains("UpDown"))
                        {
                            DragY = true;
                            DragX = DragZ = false;
                        }
                        if(hit.Node.Name.Contains("LeftRight"))
                        {
                            DragX = true;
                            DragY = DragZ = false;
                        }
                        if(hit.Node.Name.Contains("BackFor"))
                        {
                            DragZ = true;
                            DragX = DragY = false;
                        }

                    }
                    // Environment.Exit(1);
                }
                else
                {
                    DragX = DragY = DragZ = false;
                    SelectedEntity = null;
                    GizmoTranslate.SetDoRender(false);
                }

                //ge.Position = new float3()


            }
        }

        

        private void Viewer_MouseMove(object sender, MouseEventArgs e)
        {

            if (firstMove)
            {
                cp = 0;
                cy = 0;
                lx = e.X;
                ly = e.Y;
                firstMove = false;
            }

            int mx = e.X - lx;
            int my = e.Y - ly;


            if (camRot)
            {
                cp = cp + (float)(my) * 0.5f;
                cy = cy + (float)(mx) * 0.5f;
            }
            lx = e.X;
            ly = e.Y;

            if (DragY)
            {

                if (SelectedEntity != null)
                {
                    switch (EMode)
                    {
                        case EditMode.Translate:
                            SelectedEntity.Move(0, -my * 0.025f, 0);
                            break;
                        case EditMode.Rotate:
                            SelectedEntity.TurnLocal(0, -mx * 0.25f, 0);
                            break;
                    }
                    GizmoTranslate.Position = SelectedEntity.GetGlobalPos();
                }

            }
            if (DragX)
            {
                if (SelectedEntity != null)
                {
                    switch (EMode)
                    {

                        case EditMode.Translate:
                            SelectedEntity.Move(mx * 0.025f, 0, 0);
                            break;
                        case EditMode.Rotate:
                            SelectedEntity.TurnLocal(my * 0.25f, 0,0);
                            break;
                    }
                    GizmoTranslate.Position = SelectedEntity.GetGlobalPos();
                }

            }
            if (DragZ)
            {
                if (SelectedEntity != null)
                {
                    switch (EMode)
                    {
                        case EditMode.Translate:
                            SelectedEntity.Move(0, 0, my * 0.025f);
                            break;
                        case EditMode.Rotate:
                            SelectedEntity.TurnLocal(0, 0, mx * 0.25f);
                            break;
                    }
                    GizmoTranslate.Position = SelectedEntity.GetGlobalPos();
                }

            }
            if (camRot)
            {
                Cam.SetRotation(cp, cy, 0);
            }
        }
    }

    public enum EditMode
    {
        Translate,Rotate,Scale
    }
    public enum SpaceMode
    {
        Global,Local
    }

}
