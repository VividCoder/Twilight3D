#include "pch.h"
#include "VMesh3D.h"
#include "MathsUtil.h"

#include "Intersection.h"

using namespace Vivid::Mesh;
using namespace Diligent;

 Mesh3D::Mesh3D(int vertexNum, int indexNum) {

     vertices.resize(0);
     indices.resize(0);

     for (int i = 0; i < vertexNum; i++) {


         Vertex3D* nv = new Vertex3D;

         nv->Pos = float3(0, 0, 0);
         nv->Normal = float3(0, 0, 0);
         nv->Tangent = float3(0, 0, 0);
         nv->BiNormal = float3(0, 0, 0);

         vertices.push_back(nv);

     }

     for (int i = 0; i < indexNum; i++) {

         Tri* t = new Tri;

         t->V0 = 0;
         t->V1 = 0;
         t->V2 = 0;

         indices.push_back(t);

     }

     material = new Vivid::Material::Material();

}

 bool Mesh3D::RayToTri(float4x4 mat, float3 origin, float3 vec, float3& out) {

     float sd = 100000.0f;
     float3 shit;
     bool first = true;

//     printf("Checking mesh. Tris:%d \n", indices.size());

     for (int i = 0; i < indices.size(); i++) {

         float3 v0, v1, v2;

         v0 = vertices[indices[i]->V0]->Pos * mat;
         v1 = vertices[indices[i]->V1]->Pos * mat;
         v2 = vertices[indices[i]->V2]->Pos * mat;
         //printf("X:%4.2f Y:%4.2f Z:%4.2f \n", v0.x, v0.y, v0.z);

         float3 out2;

         if (Vivid::Intersections::Intersection::RayToTri(origin, vec, v0, v1, v2, out2)) {

         //    printf("Intersection!\n");

             float dis = Maths::MathsUtil::Distance(origin, out2);
             if (dis < sd || first) {
                 sd = dis;
                 first = false;
                 shit = out2;
             }

         }

     }
     if (first) {

  //       printf("No hit!\n");
         return false;

     }
     else {

         out = shit;
    //     printf("Got a hit.\n");

         return true;

     }



 }

 BoundingBox* Mesh3D::GetBounds(float4x4 m) {

     float sx, sy, sz;
     float bx, by, bz;
     sx = sy = sz = 10000.0f;
     bx = by = bz = -10000.0f;

     for (int i = 0; i < vertices.size();i++) {

         auto v = vertices[i];

         float3 ap = v->Pos * m;


         if (ap.x < sx)
         {
             sx = ap.x;
         }
         if ( ap.y < sy) {
             sy = ap.y;
         }
         if ( ap.z < sz) {
             sz = ap.z;
         }

         if (ap.x > bx)
         {
             bx = ap.x;
         }
         if (ap.y > by) {
             by = ap.y;
         }
         if (ap.z > bz) {
             bz = ap.z;
         }

     }

     bb = new BoundingBox;

     bb->SX = sx;
     bb->SY = sy;
     bb->SZ = sz;

     bb->BX = bx;
     bb->BY = by;
     bb->BZ = bz;

     bb->BW = bx - sx;
     bb->BH = by - sy;
     bb->BD = bz - sz;

     bb->CX = sx + (bx - sx) / 2.0f;
     bb->CY = sy + (by - sy) / 2.0f;
     bb->CZ = sz + (bz - bz) / 2.0f;

     printf("sx:%4.2f sy:%4.2f sz:%4.2f bx:%4.2f by:%4.2f bz:%4.2f w:%4.2f h:%4.2f d:%4.2f \n", sx, sy, sz, bx, by, bz, bb->BW, bb->BH, bb->BD);

     
     return bb;

 }

 void Mesh3D::SetVertex(int index, Vertex3D* v) {

     Vertex3D* gv = vertices.at(index);
     gv->Pos = v->Pos;
     gv->Normal = v->Normal;
     gv->BiNormal = v->BiNormal;
     gv->Tangent = v->Tangent;
     gv->UV = v->UV;

}


 void Mesh3D::SetTri(int index, Tri* t) {

     Tri* gt = indices.at(index);

     gt->V0 = t->V0;
     gt->V1 = t->V1;
     gt->V2 = t->V2;

 
 }

 void Mesh3D::Final() {

     vector<Uint32> i1;

     i1.resize(0);

     for (int i = 0; i < indices.size(); i++) {

         auto t = indices.at(i);

         i1.push_back((Uint32)t->V0);
         i1.push_back((Uint32)t->V1);
         i1.push_back((Uint32)t->V2);

     }

     vb = new VertexBuffer3D(vertices, i1);


 };