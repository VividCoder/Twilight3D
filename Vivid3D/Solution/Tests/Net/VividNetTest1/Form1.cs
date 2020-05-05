using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VividNetTest1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Console.WriteLine("Testing .DLL");
            Console.WriteLine("V:"+VividNet.Bind.VBind.testBind(4));
            while (true) { }



        }
    }
}
