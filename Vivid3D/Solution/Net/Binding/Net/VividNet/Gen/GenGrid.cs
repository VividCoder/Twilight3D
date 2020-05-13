using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Mesh;

namespace VividNet.Gen
{
    public class GenGrid 
    {


        public static void AddHLine(Mesh3D mesh,float x,float y,float height,int vn,int tn)
        {
            float siz = 0.15f;

            Vertex3D v1, v2, v3, v4;

            v1 = new Vertex3D(new Math.float3(x, 0, y));
            v2 = new Vertex3D(new Math.float3((float)x + siz, 0, y));
            v3 = new Vertex3D(new Math.float3((float)x + siz, 0, y + height));
            v4 = new Vertex3D(new Math.float3((float)x, 0,y + height));

            Tri t1, t2, t3, t4;

            t1 = new Tri(vn, vn + 1, vn + 2);
            t2 = new Tri(vn + 2, vn + 3, vn);
            t3 = new Tri(vn, vn + 2, vn + 1);
            t4 = new Tri(vn + 2, vn, vn + 3);

            mesh.SetVertex(vn, v1);
            mesh.SetVertex(vn+1, v2);
            mesh.SetVertex(vn+2, v3);
            mesh.SetVertex(vn+3, v4);

            mesh.SetTri(tn, t1);
            mesh.SetTri(tn + 1, t2);
            mesh.SetTri(tn + 2, t3);
            mesh.SetTri(tn + 3, t4);

        }
            
            

        public static void AddVLine(Mesh3D mesh,float x,float y,float width,int vn,int tn)
        {
            float siz = 0.15f;

            Vertex3D v1, v2, v3, v4;

            v1 = new Vertex3D(new Math.float3(x, 0, y));
            v2 = new Vertex3D(new Math.float3((float)x, 0, y+siz));
            v3 = new Vertex3D(new Math.float3((float)x+width, 0, y+siz ));
            v4 = new Vertex3D(new Math.float3((float)x+width, 0, y));

            Tri t1, t2, t3, t4;

            t1 = new Tri(vn, vn + 1, vn + 2);
            t2 = new Tri(vn + 2, vn + 3, vn);
            t3 = new Tri(vn, vn + 2, vn + 1);
            t4 = new Tri(vn + 2, vn, vn + 3);

           mesh.SetVertex(vn, v1);
            mesh.SetVertex(vn + 1, v2);
            mesh.SetVertex(vn + 2, v3);
            mesh.SetVertex(vn + 3, v4);

            mesh.SetTri(tn, t1);
            mesh.SetTri(tn + 1, t2);
            mesh.SetTri(tn + 2, t3);
            mesh.SetTri(tn + 3, t4);

        }

        public static Scene.Nodes.NodeEntity Grid(float size)
        {

            var ent = new Scene.Nodes.NodeEntity();

            var mesh = new Mesh3D(((int)size) * 16, (int)size * 16) ;

            float sx, sz;

            sx = -size;
            sz = -size;

            int verts = (int)(size * 2 * 4 * 2);
            int tris = (int)(size * 2 * 2 * 2);

            int vn, tn;
            vn = tn = 0;

            for(int i = (int)-size; i < (int)size; i += 2)
            {

                AddHLine(mesh, i, -size, size*2, vn, tn);
                vn += 4;
                tn += 4;

            }

            for(int i = (int)-size; i < size; i += 2)
            {

                AddVLine(mesh, -size, i,size*2, vn, tn);
                vn += 4;
                tn += 4;

            }


            ent.AddMesh(mesh);
             
            mesh.Final();

            return ent;

        }

    }
}
