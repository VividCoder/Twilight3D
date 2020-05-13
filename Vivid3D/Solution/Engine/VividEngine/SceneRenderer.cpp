#include "pch.h"
#include "SceneRenderer.h"
#include "VMesh3D.h"
#include "NodeLight.h"
#include "Material.h"

using namespace Vivid::Renderer;

Vivid::Renderer::States::RenderState3DNormal *s1;

float4x4 mvp;

float4x4 mview;
float4x4 mmodel;
float4x4 mproj;

vector<Vivid::Scene::Nodes::NodeLight*> light;

Vivid::Scene::Nodes::NodeCam* cam;

Vivid::Scene::Nodes::VSceneEntity* ent;

SceneRenderer::SceneRenderer(Vivid::Scene::SceneBase* scene)
{

	pScene = scene;
	rs1 = new Vivid::Renderer::States::RenderState3DNormal();
    s1 = rs1;


};

void render_mesh(Vivid::Mesh::Mesh3D* mesh) {


	 auto devCon = Vivid::App::VividApp::GetDeviceContext();



     // Set the pipeline state
     devCon->SetPipelineState(s1->GetState());
     devCon->CommitShaderResources(s1->GetBinding(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
     auto rb = s1->GetBinding();

     auto mat = mesh->GetMaterial();
     

     //if (mat->hasDiffuse()) {




         //if(mat->)

        // DBOUT("Tex:" << mat->GetDiffuse()->GetPath() << "\n");
       
         rb->GetVariableByName(SHADER_TYPE_PIXEL, "color_Texture")->Set(mat->GetDiffuse()->GetView());
         rb->GetVariableByName(SHADER_TYPE_PIXEL, "normal_Texture")->Set(mat->GetNormal()->GetView());

     //}

     





    // Bind vertex and index buffers
    Uint32   offset = 0;
    IBuffer* pBuffs[] = {  mesh->GetVB()->GetVBuf() };
    devCon->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    devCon->SetIndexBuffer(mesh->GetVB()->GetIBuf(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


    struct Constants {

        float4x4 g_View;
        float4x4 g_Model;
        float4x4 g_Projection;
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

        if (first && light.size()>1) {

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

void render_node(Vivid::Scene::VSceneNode* node) {

    Vivid::Scene::Nodes::VSceneEntity* nEnt = (Vivid::Scene::Nodes::VSceneEntity*)node;

   // DBOUT("Rendering Node:" << node->GetName() << " Meshes:" << nEnt->MeshCount() << " \n");


    auto isn = dynamic_cast<Vivid::Scene::Nodes::VSceneEntity*>(node);

    if (isn == NULL) {
  
    }
    else {
        //    return 2;


        mvp = node->GetWorld() * cam->GetWorld();


        //mvp = mvp * float4x4::Projection(45.0f, 800.0f / 600.0f , 0.1f, 1000.f, false);

        mmodel = node->GetWorld();


        for (int i = 0; i < nEnt->MeshCount(); i++) {

            auto msh = nEnt->GetMesh(i);

            ent = nEnt;

            render_mesh(msh);

        };

    }
    for (int i = 0; i<node->NodeCount(); i++) {

        auto n2 = node->GetNode(i);

        render_node(n2);

    }

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