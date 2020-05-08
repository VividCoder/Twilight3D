using ComponentFactory.Krypton.Navigator;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VividEditor
{
    public partial class Form1 : ComponentFactory.Krypton.Toolkit.KryptonForm
    {
        public Form1()
        {
            InitializeComponent();
            kryptonDockingManager1.AddToWorkspace("Workspace",new KryptonPage[] { new UserControl1() });
        }
    }
}
