#include "pch.h"
#include "SceneRenderer.h"
#include "VMesh3D.h"
#include "Material.h"

using namespace Vivid::Renderer;

Vivid::Renderer::States::RenderState3DNormal *s1;

float4x4 mvp;

Vivid::Scene::Nodes::NodeCam* cam;

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
     

     if (mat->hasDiffuse()) {



         //if(mat->)

        // DBOUT("Tex:" << mat->GetDiffuse()->GetPath() << "\n");
       
         rb->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Set(mat->GetDiffuse()->GetView());
     }





    // Bind vertex and index buffers
    Uint32   offset = 0;
    IBuffer* pBuffs[] = {  mesh->GetVB()->GetVBuf() };
    devCon->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    devCon->SetIndexBuffer(mesh->GetVB()->GetIBuf(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


 

    {
        // Map the buffer and write current world-view-projection matrix
        MapHelper<float4x4> CBConstants(devCon, s1->GetConsts(), MAP_WRITE, MAP_FLAG_DISCARD);
        *CBConstants = mvp.Transpose();

    }

    // Commit shader resources. RESOURCE_STATE_TRANSITION_MODE_TRANSITION mode
    // makes sure that resources are transitioned to required states.


    DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
    DrawAttrs.IndexType = VT_UINT32; // Index type
    DrawAttrs.NumIndices = mesh->IndicesNum() * 3;
    // Verify the state of vertex and index buffers
    DrawAttrs.Flags = DRAW_FLAG_VERIFY_ALL;
    devCon->DrawIndexed(DrawAttrs);
 //   rb->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Release();

}

void render_node(Vivid::Scene::VSceneNode* node) {

    Vivid::Scene::Nodes::VSceneEntity* nEnt = (Vivid::Scene::Nodes::VSceneEntity*)node;

   // DBOUT("Rendering Node:" << node->GetName() << " Meshes:" << nEnt->MeshCount() << " \n");

    mvp = node->GetWorld() * cam->GetWorld();


    mvp = mvp * float4x4::Projection(45.0f, 800.0f / 600.0f , 0.1f, 1000.f, false);
   
   
    for (int i = 0; i < nEnt->MeshCount(); i++) {

        auto msh = nEnt->GetMesh(i);



        render_mesh(msh);

    };

    for (int i = 0; i<node->NodeCount(); i++) {

        auto n2 = node->GetNode(i);

        render_node(n2);

    }

}

void SceneRenderer::Render() {


    //mvp = float4x4::Projection(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f, false);
    


    cam = pScene->GetCam();

    
    render_node(pScene->GetRoot());

};

void SceneRenderer::Build() {


};

void SceneRenderer::Bind() {


};