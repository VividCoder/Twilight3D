using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Math
{
    public class Maths
    {

        public static float PI = 3.14159265358979323846f;

        public static float DegToRad(float deg)
        {

            return (deg * PI) / 180.0f;

        }


        public static float RadToDeg(float rad)
        {

            return (rad * 180.0f) / PI;

        }

    }
}
