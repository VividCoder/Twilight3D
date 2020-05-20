using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Texture;

namespace VividNet.Material
{
    public class MaterialBase : VividObj
    {
    
        public MaterialBase(IntPtr id)
        {

            ID = id;

        }

        public MaterialBase()
        {

            ID = BindMat.vNewMaterial();

        }

        public Texture2D GetDiffuse()
        {

            return new Texture2D(BindMat.vMatGetDiffuse(ID));


        }

        public Texture2D GetNormal()
        {

            return new Texture2D(BindMat.vMatGetNormal(ID));

        }

        public void SetDiffuse(Texture2D tex)
        {

            BindMat.vMatSetDiffuse(ID, tex.ID);

        }
    
        public void SetNormal(Texture2D tex)
        {

            BindMat.vMatSetNormal(ID, tex.ID);


        }

    }

}
