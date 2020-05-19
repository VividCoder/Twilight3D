namespace VividSceneEditor
{
    partial class SceneGraph
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.graphTree = new ComponentFactory.Krypton.Toolkit.KryptonTreeView();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.modulesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addNodeModuleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // graphTree
            // 
            this.graphTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphTree.Location = new System.Drawing.Point(0, 0);
            this.graphTree.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.graphTree.Name = "graphTree";
            this.graphTree.Size = new System.Drawing.Size(355, 533);
            this.graphTree.TabIndex = 0;
            this.graphTree.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.kryptonTreeView1_AfterSelect);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.modulesToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(211, 56);
            // 
            // modulesToolStripMenuItem
            // 
            this.modulesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addNodeModuleToolStripMenuItem});
            this.modulesToolStripMenuItem.Name = "modulesToolStripMenuItem";
            this.modulesToolStripMenuItem.Size = new System.Drawing.Size(210, 24);
            this.modulesToolStripMenuItem.Text = "Modules";
            // 
            // addNodeModuleToolStripMenuItem
            // 
            this.addNodeModuleToolStripMenuItem.Name = "addNodeModuleToolStripMenuItem";
            this.addNodeModuleToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.addNodeModuleToolStripMenuItem.Text = "Add Node Module";
            this.addNodeModuleToolStripMenuItem.Click += new System.EventHandler(this.addNodeModuleToolStripMenuItem_Click);
            // 
            // SceneGraph
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(355, 533);
            this.Controls.Add(this.graphTree);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "SceneGraph";
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private ComponentFactory.Krypton.Toolkit.KryptonTreeView graphTree;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem modulesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addNodeModuleToolStripMenuItem;
    }
}
