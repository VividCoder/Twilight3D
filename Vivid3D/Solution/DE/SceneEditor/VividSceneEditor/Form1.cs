using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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


        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
