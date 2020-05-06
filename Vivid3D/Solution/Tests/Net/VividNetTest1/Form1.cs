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
            // while (true) { }
            //var Hwnd = static_Cast<HWMD
            IntPtr hwd = this.Handle;
            VividNet.Bind.VBind.initWinHW(hwd);

          //  Console.WriteLine(Environment.CurrentDirectory);
  //          while (true) { }

            var tex1 = new VividNet.Texture.Texture2D("tex1.png");

        }
        

        private void timer1_Tick(object sender, EventArgs e)
        {
            VividNet.Bind.VBind.vRender();


            VividNet.Bind.VBind.vPresent();
            Console.WriteLine("Ticked");
        }
    }
}
