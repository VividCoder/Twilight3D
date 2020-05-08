﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Math;

namespace VividNet.Scene.Nodes
{
    public class NodeLight : SceneNode
    { 
    
         public Color Diffuse
        {
            get
            {
                return _Diff;
            }
            set
            {
                _Diff = value;
                BindLight.vLightSetDiff(ID, value.R, value.G, value.B);
            }
        }

        private Color _Diff;

         public NodeLight()
        {

            ID = BindLight.vNewLight();
            Diffuse = new Color(1, 1, 1);


        }

        public void SetDiffuse(float r,float g,float b)
        {

            Diffuse = new Color(r, g, b);
            
        }

    }
}