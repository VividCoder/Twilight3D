using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;

namespace VividNet.Bind
{
    class BindMat
    {

        [DllImport("VividBind.dll")]
        public extern static void vMatSetDiffuse(IntPtr mat, IntPtr tex);

        [DllImport("VividBind.dll")]
        public extern static void vMatSetNormal(IntPtr mat, IntPtr tex);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vNewMaterial();

        [DllImport("VividBind.dll")]
        public extern static IntPtr vMatGetDiffuse(IntPtr mat);

        [DllImport("VividBind.dll")]
        public extern static IntPtr vMatGetNormal(IntPtr mat);


    }
}
