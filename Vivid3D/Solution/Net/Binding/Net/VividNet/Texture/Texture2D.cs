using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
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

            ID = BindTexture.vLoadTexture2D(path,0);
     

        }

        public static Texture2D QuickLoad(string path)
        {
            if(File.Exists(path+".cache"))
            {
                FileStream fi = new FileStream(path + ".cache", FileMode.Open, FileAccess.Read);
                BinaryReader br = new BinaryReader(fi);

                int cw = br.ReadInt32();
                int ch = br.ReadInt32();
                int bpp = br.ReadInt32();
                byte[] cdat = br.ReadBytes(cw * ch * bpp);
                br.Close();
                fi.Close();
                return new Texture2D(cdat, cw, ch);


            }
            Bitmap map = new Bitmap(path);

            int w = map.Width;
            int h = map.Height;

            byte[] data = new byte[w * h * 3];
            int dl = 0;

            for(int y = 0; y < h; y++)
            {
                for(int x = 0; x < w; x++)
                {
                    var pix = map.GetPixel(x, y);
                    data[dl++] = pix.R;
                    data[dl++] = pix.G;
                    data[dl++] = pix.B;
                }
            }

            FileStream fs = new FileStream(path + ".cache", FileMode.Create, FileAccess.Write);
            BinaryWriter bw = new BinaryWriter(fs);

            bw.Write(w);
            bw.Write(h);
            bw.Write(3);
            bw.Write(data);

            bw.Flush();
            fs.Flush();
            bw.Close();
            fs.Close();

            return new Texture2D(data, w, h);

        }

        public Texture2D(byte[] data,int w,int h)
        {
            ID = BindTexture.vCreateTexture2D(data, w, h,3);
        }
    }
}
