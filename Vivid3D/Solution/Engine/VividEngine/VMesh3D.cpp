#include "pch.h"
#include "VMesh3D.h"

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