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
