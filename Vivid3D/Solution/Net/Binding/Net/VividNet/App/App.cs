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

        public static void SetSize(int w,int h)
        {

            BindApp.vAppSetSize(w, h);

        }


    }
}
