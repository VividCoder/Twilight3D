using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;

namespace VividNet.Texture
{
    public class Texture2D : VividObj
    {

        public Texture2D(string path)
        {

            ID = BindTexture.vLoadTexture2D(Environment.CurrentDirectory+"\\"+path);

        }

    }
}
