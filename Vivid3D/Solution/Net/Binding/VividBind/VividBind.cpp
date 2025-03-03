// VividBind.cpp : Defines the exported functions for the DLL.
//
#include "pch.h"

#include <VividApp.h>

#include "VMesh2D.h"
#include "Draw2D.h"
#include "Texture2D.h"
#include "SceneBase.h"
#include "Importer.h"
#include "SceneRenderer.h"
#include "NodeLight.h"
#include "BoundingBox.h"
using namespace Vivid::App;

#include "framework.h"
#include "VividBind.h"

#include <iostream>

#include "EngineMain.h"


// This is an example of an exported variable
VIVIDBIND_API int nVividBind=0;

// This is an example of an exported function.
VIVIDBIND_API int fnVividBind(void)
{
    return 0;
}

extern "C" {

    VIVIDBIND_API Vivid::Draw::Draw2D* vNewDraw2D() {

        return new Vivid::Draw::Draw2D();

    }

    VIVIDBIND_API void vDraw2D_Rect(Vivid::Draw::Draw2D* d2d, int x, int y, int w, int h) {

        d2d->Rect(x, y, w, h);

    }

    VIVIDBIND_API void vDraw2D_SetTexture(Vivid::Draw::Draw2D* d2d, Vivid::Texture::Texture2D* tex)
    {

        d2d->SetTexture(tex);

    }

    VIVIDBIND_API void vDraw2D_Bind(Vivid::Draw::Draw2D* d2d) {

        d2d->Bind();

    }

    // :- Material 

    VIVIDBIND_API Vivid::Material::Material * vNewMaterial() {

        return new Vivid::Material::Material;

    };

    VIVIDBIND_API void vMatSetDiffuse(Vivid::Material::Material * mat, Vivid::Texture::Texture2D* tex) {

        mat->SetDiffuse(tex);

    };

    VIVIDBIND_API void vMatSetNormal(Vivid::Material::Material* mat, Vivid::Texture::Texture2D* tex) {

        mat->SetNormal(tex);

    };



    // SCENE

    VIVIDBIND_API Vivid::Scene::SceneBase* vNewScene() {

        return new Vivid::Scene::SceneBase();

    }

    VIVIDBIND_API Vivid::Scene::SceneHit* vSceneRayToTri(Vivid::Scene::SceneBase* scene, float ox, float oy, float oz, float vx, float vy, float vz)
    {

        return scene->RayToTri(float3(ox, oy, oz), float3(vx, vy, vz));

    }

    VIVIDBIND_API Vivid::Scene::SceneHit* vSceneCamPick(Vivid::Scene::SceneBase* scene, int mx, int my) {

        return scene->CamPick(mx, my);

    }

    VIVIDBIND_API void vSetCanPick(Vivid::Scene::Nodes::VSceneEntity* ent, int can)
    {

        if (can) {
            ent->SetCanPick(true);
        } else{
            ent->SetCanPick(false);
        }

    }

    VIVIDBIND_API int vCanPick(Vivid::Scene::Nodes::VSceneEntity* ent) {

        if (ent->CanPick()) {
            return 1;
        }
        else {
            return 0;
        }

    }

    VIVIDBIND_API Vivid::Scene::Nodes::VSceneEntity* vSceneHitEntity(Vivid::Scene::SceneHit* hit) {

        return hit->Entity;

    }

    VIVIDBIND_API float vSceneHitPX(Vivid::Scene::SceneHit* hit) {

        return hit->pos.x;

    }

    VIVIDBIND_API float vSceneHitPY(Vivid::Scene::SceneHit* hit) {

        return hit->pos.y;

    }

    VIVIDBIND_API float vSceneHitPZ(Vivid::Scene::SceneHit* hit) {

        return hit->pos.z;

    }

    VIVIDBIND_API int vSceneHitHit(Vivid::Scene::SceneHit* hit) {

        if (hit->hit) {
            return 1;
        }
        return 0;


    }


    VIVIDBIND_API float vSceneHitDis(Vivid::Scene::SceneHit* hit) {

        return hit->dis;

    }


    VIVIDBIND_API Vivid::Scene::VSceneNode* vNewSceneNode() {

        return new Vivid::Scene::VSceneNode();

    }

    VIVIDBIND_API void vNodeMove(Vivid::Scene::VSceneNode* node, float x, float y, float z) {

        node->Move(x, y, z);

    }

    VIVIDBIND_API void vSceneSetRoot(Vivid::Scene::SceneBase* scene, Vivid::Scene::VSceneNode* node) {

        scene->SetRoot(node);

    }

    VIVIDBIND_API void vSceneNodeAddNode(Vivid::Scene::VSceneNode* node1, Vivid::Scene::VSceneNode* node2) {

        printf("Node>>");
        printf(node1->GetName());
        printf("\n");
        printf("Added>>");
        printf(node2->GetName());
        printf("\n");

        node1->AddNode(node2);
        printf("NC:%d\n", node1->NodeCount());

    }

    VIVIDBIND_API int vSceneNodeNodeCount(Vivid::Scene::VSceneNode* node) {

        return node->NodeCount();

    }

    VIVIDBIND_API Vivid::Scene::VSceneNode* vSceneNodeGetNode(Vivid::Scene::VSceneNode* node, int num) {

        return node->GetNode(num);

    }

    VIVIDBIND_API int vSceneNodeGetType(Vivid::Scene::VSceneNode* node) {
        
        auto isn = dynamic_cast<VSceneEntity*>(node);

        if (isn == NULL) {
            return 1;
        }
        else {
            return 2;
        }
        return 0;

      
    }

    VIVIDBIND_API const char* _vSceneNodeGetName(Vivid::Scene::VSceneNode* node) {

        return node->GetName();

    }

    VIVIDBIND_API void vSceneNodeSetName(Vivid::Scene::VSceneNode* node, const char* name)
    {
        
        node->SetName(name);

    }

    VIVIDBIND_API void vSceneNodeSetNameRC(Vivid::Scene::VSceneNode* node, const char* name) {

        node->SetNameRC(name);

    }

    VIVIDBIND_API void vNodeRotateLocal(Vivid::Scene::VSceneNode* node, float pitch, float yaw, float roll) {

        node->TurnLocal(pitch, yaw, roll);

    }
    
    VIVIDBIND_API void vNodeRotateGlobal(Vivid::Scene::VSceneNode* node, float pitch, float yaw, float roll) {

        node->TurnGlobal(pitch, yaw, roll);

    }




    VIVIDBIND_API void vSceneRender(Vivid::Scene::SceneBase* scene) {

        

    }

    VIVIDBIND_API void vSceneNodeSetPos(Vivid::Scene::VSceneNode* node, float x, float y, float z) {

        node->SetPosition(x, y, z);

    }

    VIVIDBIND_API float vSceneGetGlobalPosX(Vivid::Scene::VSceneNode* node) {

        return node->GetGlobalPos().x;

    }

    VIVIDBIND_API float vSceneGetGlobalPosY(Vivid::Scene::VSceneNode* node) {

        return node->GetGlobalPos().y;

    }

    VIVIDBIND_API float vSceneGetGlobalPosZ(Vivid::Scene::VSceneNode* node) {

        return node->GetGlobalPos().z;

    }

    VIVIDBIND_API void vEntitySetDoRender(Vivid::Scene::Nodes::VSceneEntity* node,int render) {

        node->SetDoRender(render == 1);

    }

    VIVIDBIND_API int vEntityGetDoRender(Vivid::Scene::Nodes::VSceneEntity* node)
    {

        if (node->GetDoRender()) {
            return 1;
        }
        return 0;

    }




    VIVIDBIND_API float vSceneNodeGetPosX(Vivid::Scene::VSceneNode* node) {

        return node->GetPosition().x;

    }

    VIVIDBIND_API float vSceneNodeGetPosY(Vivid::Scene::VSceneNode* node) {

        return node->GetPosition().y;

    }
    VIVIDBIND_API float vSceneNodeGetPosZ(Vivid::Scene::VSceneNode* node) {

        return node->GetPosition().z;

    }

    VIVIDBIND_API Vivid::Scene::Nodes::NodeCam* vSceneGetCam(Vivid::Scene::SceneBase* scene) {

        return scene->GetCam();

    }

    VIVIDBIND_API void vSceneNodeSetRotate(Vivid::Scene::VSceneNode* node, float pitch, float yaw, float roll) {

        node->SetRotation(pitch, yaw, roll);

    }

    // :- App

    VIVIDBIND_API void vAppSetSize(int w, int h) {

        VividApp::SetSize(w, h);

    }


    // :- Meshes

    VIVIDBIND_API Vivid::Mesh::Mesh3D* vNewMesh(int vertices, int tris) {

        return new Vivid::Mesh::Mesh3D(vertices, tris);

    }

    VIVIDBIND_API void vMeshSetMat(Vivid::Mesh::Mesh3D* mesh, Vivid::Material::Material* mat) {

        mesh->SetMaterial(mat);

    }

    VIVIDBIND_API void vSetMeshVertex(Vivid::Mesh::Mesh3D *mesh,int ix, float x1, float y1, float z1, float u, float v, float w, float nx, float ny, float nz, float tx, float ty, float tz, float bx, float by, float bz) {

        auto vert = new Vivid::DataTypes::Vertex3D();

        vert->Pos = float3(x1, y1, z1);
        vert->Normal = float3(nx, ny, nz);
        vert->Tangent = float3(tx, ty, tz);
        vert->BiNormal = float3(bx, by, bz);
        vert->UV = float3(u, v, w);
       
        mesh->SetVertex(ix, vert);

    }

    VIVIDBIND_API void vSetMeshTri(Vivid::Mesh::Mesh3D* mesh, int ix, int v0, int v1, int v2) {

        auto tri = new Vivid::DataTypes::Tri();

        tri->V0 = v0;
        tri->V1 = v1;
        tri->V2 = v2;

        mesh->SetTri(ix, tri);

    }

    VIVIDBIND_API void vMeshFinal(Vivid::Mesh::Mesh3D* mesh) {

        mesh->Final();

    }


    VIVIDBIND_API Vivid::Material::Material* vMeshGetMat(Vivid::Mesh::Mesh3D * mesh) {

        return mesh->GetMaterial();

    }

    VIVIDBIND_API void vNodeSetRotation(Vivid::Scene::VSceneNode* node, float* mat)
    {

        float4x4 m;

        m.m00 = mat[0];
        m.m01 = mat[1];
        m.m02 = mat[2];
        m.m03 = mat[3];

        m.m10 = mat[4];
        m.m11 = mat[5];
        m.m12 = mat[6];
        m.m13 = mat[7];

        m.m20 = mat[8];
        m.m21 = mat[9];
        m.m22 = mat[10];
        m.m23 = mat[11];

        m.m30 = mat[12];
        m.m31 = mat[13];
        m.m32 = mat[14];
        m.m33 = mat[15];

        node->SetRotationMatrix(m);



    }

    VIVIDBIND_API int vMeshGetTriCount(Vivid::Mesh::Mesh3D* mesh)
    {

        return mesh->GetTriCount();

    }

    VIVIDBIND_API int vMeshGetVertexCount(Vivid::Mesh::Mesh3D* mesh)
    {

        return mesh->GetVertexCount();

    }

    VIVIDBIND_API Tri* vMeshGetTri(Vivid::Mesh::Mesh3D* mesh,int ix) {

        return mesh->GetTri(ix);

    };

    VIVIDBIND_API void vMeshTriData(Tri* t, int* data) {

        data[0] = t->V0;
        data[1] = t->V1;
        data[2] = t->V2;

    }

    VIVIDBIND_API void vMeshVertexData(Vertex3D* v, float* data)
    {
        data[0] = v->Pos.x;
        data[1] = v->Pos.y;
        data[2] = v->Pos.z;

        data[3] = v->UV.x;
        data[4] = v->UV.y;
        data[5] = v->UV.z;

        data[6] = v->Normal.x;
        data[7] = v->Normal.y;
        data[8] = v->Normal.z;

        data[9] = v->Tangent.x;
        data[10] = v->Tangent.y;
        data[11] = v->Tangent.z;

        data[12] = v->BiNormal.x;
        data[13] = v->BiNormal.y;
        data[14] = v->BiNormal.z;

    }

    VIVIDBIND_API const char* _vTextureGetPath(Vivid::Texture::Texture2D* tex) {

        return tex->GetPath();

    }

    VIVIDBIND_API Vertex3D* vMeshGetVertex(Vivid::Mesh::Mesh3D* mesh, int ix) {

        return mesh->GetVertex(ix);

    }

    void debugNode(Vivid::Scene::VSceneNode* node) {

        printf("Node:");
        printf(node->GetName());
        printf("\n");

        printf("Nodes:%d\n", node->NodeCount());
        auto isn = dynamic_cast<VSceneEntity*>(node);

        if (isn == NULL) {
           
        }
        else {
           
            int meshes = isn->MeshCount();
            printf("Meshes:%d \n", meshes);
            
            //return 2;
        }
        for (int i = 0; i < node->NodeCount(); i++) {

            debugNode(node->GetNode(i));

        }

    }

    VIVIDBIND_API void vDebugScene(Vivid::Scene::SceneBase* scene) {

        printf("-------------\n");
        debugNode(scene->GetRoot());

    }

    VIVIDBIND_API void vNodeGetRotation(Vivid::Scene::VSceneNode* node,float *mat) {

        float4x4 r = node->GetRotation();
        mat[0] = r.m00;
        mat[1] = r.m01;
        mat[2] = r.m02;
        mat[3] = r.m03;
        mat[4] = r.m10;
        mat[5] = r.m11;
        mat[6] = r.m12;
        mat[7] = r.m13;
        mat[8] = r.m20;
        mat[9] = r.m21;
        mat[10] = r.m22;
        mat[11] = r.m23;
        mat[12] = r.m30;
        mat[13] = r.m31;
        mat[14] = r.m32;
        mat[15] = r.m33;
    }

    VIVIDBIND_API Vivid::Texture::Texture2D* vMatGetDiffuse(Vivid::Material::Material* mat) {

        return mat->GetDiffuse();

    }

    VIVIDBIND_API Vivid::Texture::Texture2D* vMatGetNormal(Vivid::Material::Material* mat) {

        return mat->GetNormal();

    }

    // :- Lights

    VIVIDBIND_API void vSceneAddLight(Vivid::Scene::SceneBase* scene, Vivid::Scene::Nodes::NodeLight *light) {

        scene->AddLight(light);

    }

    VIVIDBIND_API void vLightSetSpec(Vivid::Scene::Nodes::NodeLight* light, float r, float g, float b) {


        light->SetSpecular(r, g, b);

    }

    VIVIDBIND_API Vivid::Scene::Nodes::NodeLight* vNewLight() {

        return new Vivid::Scene::Nodes::NodeLight();

    }

    VIVIDBIND_API void vLightSetDiff(Vivid::Scene::Nodes::NodeLight *l, float r, float g, float b) {

        l->SetDiffuse(r, g, b);

    }

    // :- Entity

    VIVIDBIND_API Vivid::Scene::Nodes::VSceneEntity* vNewEntity() {

        return new Vivid::Scene::Nodes::VSceneEntity();


    }

    VIVIDBIND_API BoundingBox* vMeshGetBounds(Vivid::Scene::Nodes::VSceneEntity * ent,Vivid::Mesh::Mesh3D* mesh) {

        return mesh->GetBounds(ent->GetWorld());


    }

    VIVIDBIND_API int vEntityMeshCount(Vivid::Scene::Nodes::VSceneEntity* ent) {

        return ent->MeshCount();

    }

    VIVIDBIND_API Vivid::Mesh::Mesh3D* vEntityGetMesh(Vivid::Scene::Nodes::VSceneEntity* ent, int i) {

        return ent->GetMesh(i);

    }

    VIVIDBIND_API void vEntityAddMesh(Vivid::Scene::Nodes::VSceneEntity * ent,Vivid::Mesh::Mesh3D* mesh) {

        ent->AddMesh(mesh);

    }

    VIVIDBIND_API void vEntitySetRenderMode(Vivid::Scene::Nodes::VSceneEntity * ent,int mode) {

        switch (mode) {
        case 0:
            ent->SetRenderMode(Vivid::Scene::Nodes::RenderMode::Lit);
            break;
        case 1:
            ent->SetRenderMode(Vivid::Scene::Nodes::RenderMode::FullBright);
            break;
        }
    }

    // :- Renderer

    VIVIDBIND_API Vivid::Renderer::SceneRenderer * vNewRenderer(Vivid::Scene::SceneBase* scene) {

        return new Vivid::Renderer::SceneRenderer(scene);

    }

    VIVIDBIND_API void vRendererRender(Vivid::Renderer::SceneRenderer* ren)
    {

        ren->Render();

    }




    // :- Import

    VIVIDBIND_API Vivid::Scene::Nodes::VSceneEntity* vImportEntityAI(const char* path) {

        return Vivid::Import::Importer::LoadEntityAI(path);

    }

    VIVIDBIND_API int testBind(int f)
    {

        return f * 2;
    }

    VIVIDBIND_API int vSetPath(const char* path) {

        Vivid::App::VividApp::SetPath(path);
        return 0;
    }

    VIVIDBIND_API void vSetImpPath(const char* path) {

        Vivid::App::VividApp::SetImpPath(path);

    }

    VIVIDBIND_API int initWinHW(HWND hw)
    {

        Vivid::Engine::initWindowHW(hw);
        return 1;

    }
    VIVIDBIND_API int vRender() {

        Vivid::Engine::eRender();
        return 1;
    }

    VIVIDBIND_API int vPresent() {

        Vivid::Engine::ePresent();
        return 1;

    }

    // :- Texture

    VIVIDBIND_API Vivid::Texture::Texture2D* vLoadTexture2D(const char* path,int useImp) {

        if (useImp) {
            return new Vivid::Texture::Texture2D(path,true);
        }
        else {
            return new Vivid::Texture::Texture2D(path, false);
        }
    }

    VIVIDBIND_API Vivid::Texture::Texture2D* vCreateTexture2D(void* data, int w, int h,int bpp  ) {

        return new Vivid::Texture::Texture2D(data, w, h,bpp);

    }

}

// This is the constructor of a class that has been exported.
CVividBind::CVividBind()
{
    return;
}
