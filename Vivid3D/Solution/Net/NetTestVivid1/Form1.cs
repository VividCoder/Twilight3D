using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VividNet.Bind;
using VividNet.Import;
using VividNet.Scene;
using VividNet.Scene.Nodes;

namespace NetTestVivid1
{
    public partial class SceneEditor : Form
    {
        public SceneEditor()
        {
            InitializeComponent();

        }



        bool ready = true;

        NodeCam cam;
        NodeLight l1; 
        VividNet.Scene.Nodes.NodeEntity e1;
        VividNet.Scene.SceneBase scene;
        VividNet.Draw.Draw2D draw = null;
        VividNet.Texture.Texture2D tex1;
        VividNet.Renderer.SceneRenderer ren;
        float a = 0;
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (ready)
            {
                viewPanel.Invalidate();
            }

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {


        }

        private void Form1_Load(object sender, EventArgs e)
        {
         
            IntPtr hwd = Handle;
            VividNet.Bind.VBind.initWinHW(viewPanel.Handle);
            VividNet.VividApp.SetSize(viewPanel.Size.Width, viewPanel.Size.Height);
            //  Console.WriteLine(Environment.CurrentDirectory);
            //          while (true) { }

            VividNet.Bind.VBind.vSetPath(Environment.CurrentDirectory + "\\");

//            draw = new VividNet.Draw.Draw2D();

            tex1 = new VividNet.Texture.Texture2D("Tex1.png"); // new VividNet.Texture.Texture2D("tex1.png");

          //.  draw.SetTexture(tex1);
            scene = new VividNet.Scene.SceneBase();

            e1 = Importer.ImportEntityAI("scene.gltf");

            l1 = new NodeLight();

            scene.AddLight(l1);
            scene.AddNode(e1);
            cam = scene.Cam;

            l1.Position = new VividNet.Math.float3(0, 10, -10);

            ren = new VividNet.Renderer.SceneRenderer(scene);

            cam.Position = new VividNet.Math.float3(0, 0, 1);

            System.Threading.Thread.Sleep(1500);

            ready = true;
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            VividNet.VividApp.SetSize(viewPanel.Size.Width, viewPanel.Size.Height);

        }

        private void viewPanel_SizeChanged(object sender, EventArgs e)
        {
            VividNet.VividApp.SetSize(viewPanel.Size.Width, viewPanel.Size.Height);
        }

        private void viewPanel_Paint(object sender, PaintEventArgs e)
        {

            if (!ready) return;
            ready = false;
            VividNet.Bind.VBind.vRender();

            //e1.SetRotation(0, a, 0);

            a = a + 1;

            float x, y;
            x = (float)Math.Cos((a * Math.PI) / 180.0f) * 15.0f;
            y = (float)Math.Sin((a * Math.PI) / 180.0f) * 15.0f;

            l1.Position = new VividNet.Math.float3(x, 0, y);

            //  draw.Use();

            //   draw.Rect(20, 20, 200, 200);


            ren.Render();

            VividNet.Bind.VBind.vPresent();
            //Console.WriteLine("Ticked");
            ready = true;

        }
    }
}
