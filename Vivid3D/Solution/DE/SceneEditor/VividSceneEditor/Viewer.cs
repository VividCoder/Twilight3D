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

namespace VividSceneEditor
{
    public partial class Viewer : DockContent
    {
        public static VividNet.Scene.Nodes.NodeCam Cam = null;
        public static VividNet.Renderer.SceneRenderer Renderer = null;
        public static VividNet.Scene.SceneBase Scene = null;
        public static VividNet.Scene.Nodes.NodeLight Light1;
        public static VividNet.Scene.Nodes.NodeEntity Grid1;
        public Viewer()
        {
            InitializeComponent();
            Text = "View";
            CT1 = new Thread(new ThreadStart(Control_Thread));
            CT1.Priority = ThreadPriority.Normal;
            CT1.Start();

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
            Scene.AddNode(Grid1);
            Grid1.SetRenderMode(VividNet.Scene.Nodes.RenderMode.FullBright);
            //Grid1.SetRotation(90, 0, 0);

            Grid1.Position = new VividNet.Math.float3(0, 0,0);
            //base.OnLoad(e);
            Invalidate();
        }
        int x = 0;
        private void Viewer_Paint(object sender, PaintEventArgs e)
        {
            x = x + 1;
            // Scene.Root.SetRotation(x*3, x, 0);

            VividNet.Bind.VBind.vRender();

            Renderer.Render();

            VividNet.Bind.VBind.vPresent();
            Invalidate();
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
            if(e.Button == MouseButtons.Right)
            {

                camRot = false;

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

        private void Viewer_MouseDown(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
            {
                camRot = true;
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

            if (camRot)
            {
                Cam.SetRotation(cp, cy, 0);
            }
        }
    }
}
