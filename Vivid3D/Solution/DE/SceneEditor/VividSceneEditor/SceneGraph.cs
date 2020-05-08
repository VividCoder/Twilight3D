using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VividSceneEditor
{
    public partial class SceneGraph : WeifenLuo.WinFormsUI.Docking.DockContent
    {
        public SceneGraph()
        {
            InitializeComponent();
        }

        private void kryptonTreeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }
    }
}
