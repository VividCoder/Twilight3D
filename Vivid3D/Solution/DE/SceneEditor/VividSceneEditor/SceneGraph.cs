using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VividNet.Scene;
using VividNet.Scene.Nodes;
using ComponentFactory.Krypton.Toolkit;

namespace VividSceneEditor
{
    public partial class SceneGraph : WeifenLuo.WinFormsUI.Docking.DockContent
    {

        public SceneBase Scene = null;

        public SceneGraph()
        {
            InitializeComponent();
            ContextMenuStrip = contextMenuStrip1;
        }

        public void SetScene(SceneBase scene)
        {
            Scene = scene;
            Rebuild();
        }

        public void Rebuild()
        {

            graphTree.Nodes.Clear();

            TreeNode root = new TreeNode("Scene");
            
            graphTree.Nodes.Add(root);

            AddNodes(root, Scene.Root);

        }

        public void SelectNode(SceneNode node)
        {

            CheckSelect(graphTree.Nodes[0], node);


        }
        Color fc = Color.White;
        Color lc = Color.White;
        TreeNode pnode = null;
        public void CheckSelect(TreeNode node,SceneNode snode)
        {
            if (node.Tag != null)
            {
                if (snode.ID == (IntPtr)node.Tag)
                {

                    if (pnode != null)
                    {
                        pnode.BackColor = lc;
                        pnode.ForeColor = fc;
                    }

                    graphTree.SelectedNode = node;
                    lc = node.BackColor;
                    fc = node.ForeColor;
                    node.BackColor = Color.DarkBlue;
                    node.ForeColor = Color.White;
                    pnode = node;

                }
            }

            foreach(TreeNode n in node.Nodes)
            {
                CheckSelect(n, snode);
            }

        }

        public void AddNodes(TreeNode tnode,SceneNode snode)
        {

            if (snode.NotEdit) return;
            TreeNode nn = new TreeNode(snode.Name);
            nn.Tag = snode.ID;
            tnode.Nodes.Add(nn);

            foreach(var node in snode.Nodes)
            {

                AddNodes(nn, node);

            }

        }


        NewNodeModule newNodeForm;

        private void kryptonTreeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Tag == null) return;
            IntPtr id =  (IntPtr)e.Node.Tag;
            Form1.View3D.SelectNode(id);

        }

        private void addNodeModuleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var node = graphTree.SelectedNode.Tag;
            if (node != null)
            {

                var snode = Viewer.Scene.FindNode((IntPtr)node);
                if (snode != null)
                {
                    Console.WriteLine("Added module to:"+snode.Name);
                    NewNodeModule.ForNode = snode;
                    newNodeForm = new NewNodeModule();
                    newNodeForm.Show();

                }


            }
        }
    }
}
