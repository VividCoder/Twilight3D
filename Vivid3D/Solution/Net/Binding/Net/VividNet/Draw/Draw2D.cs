using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Texture;

namespace VividNet.Draw
{
    public class Draw2D : VividObj
    {

        public Texture2D BoundTex
        {
            get;
            set;
        }

       public  Draw2D()
        {

            ID = Bind.BindDraw2D.vNewDraw2D();
            BoundTex = null;

        }

        public void Rect(int x,int y,int w,int h)
        {

            Bind.BindDraw2D.vDraw2D_Rect(ID, x, y, w, h);
            
        }

        public void SetTexture(Texture2D tex)
        {
            BoundTex = tex;
            Bind.BindDraw2D.vDraw2D_SetTexture(ID, tex.ID);
        }

        public void Use()
        {

            Bind.BindDraw2D.vDraw2D_Bind(ID);

        }
       


    }
}
