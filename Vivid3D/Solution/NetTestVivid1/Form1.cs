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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            IntPtr hwd = Handle;
            VividNet.Bind.VBind.initWinHW(hwd);

            //  Console.WriteLine(Environment.CurrentDirectory);
            //          while (true) { }

            VividNet.Bind.VBind.vSetPath(Environment.CurrentDirectory + "\\");

            draw = new VividNet.Draw.Draw2D();

            tex1 = new VividNet.Texture.Texture2D("tex1.png");

            draw.SetTexture(tex1);
            scene = new VividNet.Scene.SceneBase();

            e1 = Importer.ImportEntityAI("scene.gltf");

            l1 = new NodeLight();

            scene.AddLight(l1);
            scene.AddNode(e1);
            cam = scene.Cam;

            l1.Position = new VividNet.Math.float3(0, 10, -10);

            ren = new VividNet.Renderer.SceneRenderer(scene);

            cam.Position = new VividNet.Math.float3(0, 0,1);
            ready = true;
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
                Invalidate();
            }

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {

            if (!ready) return;
            ready = false;
            VividNet.Bind.VBind.vRender();

            a = a + 1;

            float x, y;
            x =(float) Math.Cos((a * Math.PI) / 180.0f) * 15.0f;
            y =(float) Math.Sin((a * Math.PI) / 180.0f) * 15.0f;

            l1.Position = new VividNet.Math.float3(x, 0, y);



            ren.Render();

            VividNet.Bind.VBind.vPresent();
            //Console.WriteLine("Ticked");
            ready = true;
           

        }
    }
}
