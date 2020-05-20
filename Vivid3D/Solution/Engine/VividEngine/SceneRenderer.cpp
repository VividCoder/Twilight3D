#include "pch.h"
#include "SceneRenderer.h"
#include "VMesh3D.h"
#include "NodeLight.h"
#include "Material.h"

using namespace Vivid::Renderer;

Vivid::Renderer::States::RenderState3D *s1;
Vivid::Renderer::States::RenderState3DFullBright* sFB;

float4x4 mvp;

float4x4 mview;
float4x4 mmodel;
float4x4 mproj;

Vivid::Scene::Nodes::RenderMode cMode;

vector<Vivid::Scene::Nodes::NodeLight*> light;

Vivid::Scene::Nodes::NodeCam* cam;

Vivid::Scene::Nodes::VSceneEntity* ent;

SceneRenderer::SceneRenderer(Vivid::Scene::SceneBase* scene)
{

	pScene = scene;
	rsLit = new Vivid::Renderer::States::RenderState3DNormal();
    rsFB = new Vivid::Renderer::States::RenderState3DFullBright();
    s1 = rsLit;
    sFB = rsFB;



};

void render_meshFB(Vivid::Mesh::Mesh3D* mesh) {

//    printf("RenderMeshFB\n");
    RefCntAutoPtr<IDeviceContext> devCon = Vivid::App::VividApp::GetDeviceContext();
    Vivid::Material::Material* mat;
    RefCntAutoPtr<IShaderResourceBinding> rb;
    Uint32 offset = 0;
    DrawIndexedAttribs DrawAttrs;
    //printf("11\n");
    // Set the pipeline state
    devCon->SetPipelineState(sFB->GetState());
    //printf("11-2\n");
    devCon->CommitShaderResources(sFB->GetBinding(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    //printf("11-3\n");
    rb = sFB->GetBinding();


    //printf("22\n");
    mat = mesh->GetMaterial();

    rb->GetVariableByName(SHADER_TYPE_PIXEL, "color_Texture")->Set(mat->GetDiffuse()->GetView());

    //printf("33\n");
    offset = 0;
    IBuffer* pBuffs2[] = { mesh->GetVB()->GetVBuf() };
    devCon->SetVertexBuffers(0, 1, pBuffs2, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    devCon->SetIndexBuffer(mesh->GetVB()->GetIBuf(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    //printf("44\n");
    struct Constants2 {

        float4x4 g_View;
        float4x4 g_Model;
        float4x4 g_Projection;



    };

    //printf("55\n");
    MapHelper<Constants2> CBConstants2(devCon, sFB->GetConsts(), MAP_WRITE, MAP_FLAG_DISCARD);
    CBConstants2->g_View = mview.Transpose();
    CBConstants2->g_Model = mmodel.Transpose();
    CBConstants2->g_Projection = mproj.Transpose();
    //      CBConstants->lightDir = float4(0.4f, 0.3f, -0.2f, 0);

    //printf("66\n");
    devCon->CommitShaderResources(sFB->GetBinding(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    //printf("77\n");
             // This is an indexed draw call
    DrawAttrs.IndexType = VT_UINT32; // Index type
    DrawAttrs.NumIndices = mesh->IndicesNum() * 3;
    // Verify the state of vertex and index buffers
    DrawAttrs.Flags = DRAW_FLAG_VERIFY_ALL;
    devCon->DrawIndexed(DrawAttrs);
    //printf("88\n");

}

void render_meshLit(Vivid::Mesh::Mesh3D* mesh) {

    RefCntAutoPtr<IDeviceContext> devCon = Vivid::App::VividApp::GetDeviceContext();
    Vivid::Material::Material* mat;
    RefCntAutoPtr<IShaderResourceBinding> rb;
    Uint32 offset = 0;
    DrawIndexedAttribs DrawAttrs;


    //devCon = Vivid::App::VividApp::GetDeviceContext();



    // Set the pipeline state
    devCon->SetPipelineState(s1->GetState());
    devCon->CommitShaderResources(s1->GetBinding(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    rb = s1->GetBinding();

     mat = mesh->GetMaterial();


    //if (mat->hasDiffuse()) {




        //if(mat->)

       // DBOUT("Tex:" << mat->GetDiffuse()->GetPath() << "\n");

    rb->GetVariableByName(SHADER_TYPE_PIXEL, "color_Texture")->Set(mat->GetDiffuse()->GetView());
    rb->GetVariableByName(SHADER_TYPE_PIXEL, "normal_Texture")->Set(mat->GetNormal()->GetView());

    //}







   // Bind vertex and index buffers

    IBuffer* pBuffs[] = { mesh->GetVB()->GetVBuf() };
    devCon->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    devCon->SetIndexBuffer(mesh->GetVB()->GetIBuf(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


    struct Constants {

        float4x4 g_View;
        float4x4 g_Model;
        float4x4 g_Projection;
        float4x4 g_World;
        float4 lightDir;
        float4 lightPos;
        float4 lightDiff;
        float4 lightSpec;
        float4 camPos;


    };

    bool first = true;


    for (int i = 0; i < light.size(); i++) {

        auto l1 = light.at(i);

        {
            // Map the buffer and write current world-view-projection matrix
            if (first) {
                MapHelper<Constants> CBConstants(devCon, s1->GetConsts(), MAP_WRITE, MAP_FLAG_DISCARD);
                CBConstants->g_View = mview.Transpose();
                CBConstants->g_Model = mmodel.Transpose();
                CBConstants->g_Projection = mproj.Transpose();
                CBConstants->g_World = mmodel.Transpose();
                CBConstants->lightDir = float4(0.4f, 0.3f, -0.2f, 0);

                auto pos = l1->GetPosition();
                auto diff = l1->GetDiffuse();
                auto spec = l1->GetSpecular();
                auto cpos = cam->GetPosition();

                CBConstants->lightPos = float4(pos.x, pos.y, pos.z, 1.0);
                CBConstants->lightDiff = float4(diff.x, diff.y, diff.z, 1.0);
                CBConstants->lightSpec = float4(spec.x, spec.y, spec.z, 1.0);
                CBConstants->camPos = float4(cpos.x, cpos.y, cpos.z, 1.0);
                //CBConstants->lightDir;
            }
            else {

                MapHelper<Constants> CBConstants(devCon, s1->GetConsts2(), MAP_WRITE, MAP_FLAG_DISCARD);
                CBConstants->g_View = mview; // Transpose();
                CBConstants->g_Model = mmodel; // .Transpose();
                CBConstants->g_Projection = mproj.Transpose();
                CBConstants->lightDir = float4(0.4f, 0.3f, -0.2f, 0);

                auto pos = l1->GetPosition();
                auto diff = l1->GetDiffuse();
                auto spec = l1->GetSpecular();
                auto cpos = cam->GetPosition();

                CBConstants->lightPos = float4(pos.x, pos.y, pos.z, 1.0);
                CBConstants->lightDiff = float4(diff.x, diff.y, diff.z, 1.0);
                CBConstants->lightSpec = float4(spec.x, spec.y, spec.z, 1.0);
                CBConstants->camPos = float4(cpos.x, cpos.y, cpos.z, 1.0);
            }
        }

        if (first) {
            devCon->CommitShaderResources(s1->GetBinding(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

        }
        else {
            devCon->CommitShaderResources(s1->GetBinding2(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        }
        // Commit shader resources. RESOURCE_STATE_TRANSITION_MODE_TRANSITION mode
        // makes sure that resources are transitioned to required states.



        DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
        DrawAttrs.IndexType = VT_UINT32; // Index type
        DrawAttrs.NumIndices = mesh->IndicesNum() * 3;
        // Verify the state of vertex and index buffers
        DrawAttrs.Flags = DRAW_FLAG_VERIFY_ALL;
        devCon->DrawIndexed(DrawAttrs);

        if (first && light.size() > 1) {

            first = false;
            devCon->SetPipelineState(s1->GetState2());
            devCon->CommitShaderResources(s1->GetBinding2(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
            rb = s1->GetBinding2();


            rb->GetVariableByName(SHADER_TYPE_PIXEL, "color_Texture")->Set(mat->GetDiffuse()->GetView());
            rb->GetVariableByName(SHADER_TYPE_PIXEL, "normal_Texture")->Set(mat->GetNormal()->GetView());

        }
        //   rb->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Release();
    }



}

void render_mesh(Vivid::Mesh::Mesh3D* mesh) {

   
    switch (cMode) {

    case Vivid::Scene::Nodes::FullBright:

        render_meshFB(mesh);


        break;
    case Vivid::Scene::Nodes::Lit:

        render_meshLit(mesh);

        break;
    }

}

void render_node(Vivid::Scene::VSceneNode* node) {

    Vivid::Scene::Nodes::VSceneEntity* nEnt = (Vivid::Scene::Nodes::VSceneEntity*)node;

   // DBOUT("Rendering Node:" << node->GetName() << " Meshes:" << nEnt->MeshCount() << " \n");


    auto isn = dynamic_cast<Vivid::Scene::Nodes::VSceneEntity*>(node);

    if (isn == NULL) {
  
    }
    else {
        //    return 2;

        cMode = isn->GetRenderMode();

        mvp = node->GetWorld() * cam->GetWorld();


        //mvp = mvp * float4x4::Projection(45.0f, 800.0f / 600.0f , 0.1f, 1000.f, false);

        mmodel = node->GetWorld();

        if (isn->GetDoRender()) {

            for (int i = 0; i < nEnt->MeshCount(); i++) {

                auto msh = nEnt->GetMesh(i);

                ent = nEnt;

               // printf("Rendering Mesh:\n");
                render_mesh(msh);
                //printf("Rendered\n");

            };
        }

    }
    //if (isn->GetDoRender()) {
    if (isn != NULL) {
        if (isn->GetDoRender()) {
            for (int i = 0; i < node->NodeCount(); i++) {

                auto n2 = node->GetNode(i);

                //printf("Render node:\n");
                render_node(n2);
                //printf("rendered\n");


            }
        }
    }
    else {
        for (int i = 0; i < node->NodeCount(); i++) {

            auto n2 = node->GetNode(i);

            render_node(n2);

        }
    }
    //}
}

void SceneRenderer::Render() {


    mproj = float4x4::Projection(45.0f, (float)Vivid::App::VividApp::GetW() /(float)Vivid::App::VividApp::GetH(), 0.1f, 1000.0f, false);
    

     
    cam = pScene->GetCam();

    mview = cam->GetWorld();

    light = pScene->GetLights();



    render_node(pScene->GetRoot());

};

void SceneRenderer::Build() {


};

void SceneRenderer::Bind() {


};