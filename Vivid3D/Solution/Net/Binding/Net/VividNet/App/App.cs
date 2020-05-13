using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;

namespace VividNet
{
    public class VividApp
    {

        public static void InitDisplay(IntPtr win)
        {

            Bind.VBind.initWinHW(win);

        }

        public static void SetSize(int w,int h)
        {

            BindApp.vAppSetSize(w, h);

        }

        public static void SetPath(string path)
        {


            Bind.VBind.vSetPath(path);

        }

        public static void SetImpPath(string path)
        {
            Bind.VBind.vSetImpPath(path);
        }

    }
}
