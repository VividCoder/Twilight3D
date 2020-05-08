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

namespace VividSceneEditor
{
    public partial class Viewer : DockContent
    {
        public Viewer()
        {
            InitializeComponent();
            Text = "View";
        }
    }
}
