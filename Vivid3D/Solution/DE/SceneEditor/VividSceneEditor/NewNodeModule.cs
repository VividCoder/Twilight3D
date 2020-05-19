using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VividNet.Scene.Nodes;

namespace VividSceneEditor
{
    public partial class NewNodeModule : Form
    {
        public static SceneNode ForNode = null;
        public NewNodeModule()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            var modLink = Form1.CreateNodeModule(modName.Text);

            ForNode.AddModuleLink(modLink);

            Close();

        }
    }
}
