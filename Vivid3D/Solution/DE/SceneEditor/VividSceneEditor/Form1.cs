using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VividNet.Game;
using WeifenLuo.WinFormsUI.Docking;

namespace VividSceneEditor
{
    public partial class Form1 : ComponentFactory.Krypton.Toolkit.KryptonForm
    {

        public static Viewer View3D = null;
        public static SceneGraph Graph3D = null;
        public static ContentBrowser Browser;
        public static PropertiesEdit PropEdit = null;
        public static DockPanel Doc1;
        public static string ModulePath = "C:\\Content\\Modules\\";
        public static string NodeModulePath = "C:\\Content\\Modules\\NodeModules\\";

        public static GameRunner Runner = null;

        public Form1()
        {
            InitializeComponent();
            Doc1 = new DockPanel();
            this.Controls.Add(Doc1);
            //kryptonSplitContainer2.Panel1.Controls.Add(Doc1);
            Doc1.Dock = DockStyle.Fill;
      
            Graph3D = new SceneGraph();
            Graph3D.Show(Doc1, DockState.DockLeft);
            View3D = new Viewer();
            View3D.Show(Doc1, DockState.Document);

            Browser = new ContentBrowser();
            Browser.Show(Doc1, DockState.DockBottom);

            ContentBrowser.CB.SetPath("C:\\Content\\");

            PropEdit = new PropertiesEdit();
            PropEdit.Show(Doc1, DockState.DockRightAutoHide);

            Runner = new GameRunner();
            Runner.Scene = Viewer.Scene;

        }
        public static VividNet.Module.ModuleLink CreateNodeModule(string name)
        {

            var modLink = new VividNet.Module.ModuleLink();
            modLink.CodePath = NodeModulePath + name + ".cs";
            System.IO.File.Copy("Edit\\baseCode\\NodeModule.cs", modLink.CodePath);

            var text = File.ReadAllText(modLink.CodePath);
            text = text.Replace("newNodeModule", name);
            File.WriteAllText(modLink.CodePath, text);

            return modLink;

        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void toolStripButton9_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Compiling scripts");
            Runner.Scene = Viewer.Scene;
            Runner.LoadScripts();
            Runner.Run();
            Console.WriteLine("Compiled.");
        }
    }
}
