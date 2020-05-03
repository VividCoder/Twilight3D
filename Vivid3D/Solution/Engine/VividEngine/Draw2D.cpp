#include "pch.h"
#include "Draw2D.h"
#include "VertexBuffer2D.h"
#include "DataGen.h"
#include "VividApp.h"
#include "RenderState2D.h"

using namespace Vivid::Draw;

Draw2D::Draw2D() {

	cRed = cGreen = cBlue = cAlpha = 1.0f;

}

void Draw2D::Bind() {


}

void Draw2D::Release() {


}

void Draw2D::SetBlend(BlendMode mode) {

	bMode = mode;

}

void Draw2D::SetColor(float r, float g, float b, float a)
{

	cRed = r;
	cGreen = g;
	cBlue = b;
	cAlpha = a;

}

void Draw2D::SetTexture(Vivid::Texture::Texture2D* tex) {

    bTex = tex;

};

void Draw2D::Rect(int x, int y, int w, int h) {

	auto quad = Vivid::DataGen::DataGen::MakeQuad(x, y, w, h);

    quad[0]->Col = float4(cRed, cGreen, cBlue, cAlpha);
    quad[1]->Col = float4(cRed, cGreen, cBlue, cAlpha);
    quad[2]->Col = float4(cRed, cGreen, cBlue, cAlpha);
    quad[3]->Col = float4(cRed, cGreen, cBlue, cAlpha);


	Uint32 indices[] =
	{
		0,1,2, 2,3,0,
		0,2,1, 2,0,3
	};

	vector<Uint32> ind;

	ind.resize(0);

	for (int i = 0; i < 12; i++) {

		ind.push_back(indices[i]);

	}


	Vivid::Buffer::Vertex::VertexBuffer2D* vb1 = new Vivid::Buffer::Vertex::VertexBuffer2D(quad,ind);

    Vivid::RenderState::RenderState2D* ren = new Vivid::RenderState::RenderState2D();


    auto devCon = Vivid::App::VividApp::GetDeviceContext();

    float4x4 mvp = float4x4::OrthoOffCenter(0, 800, 600, 0, 0, 1, false);

    {
        // Map the buffer and write current world-view-projection matrix
        MapHelper<float4x4> CBConstants(devCon, ren->GetConsts() , MAP_WRITE, MAP_FLAG_DISCARD);
        *CBConstants = mvp.Transpose();
    }

    auto rb = ren->GetBinding();

    rb->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Set(bTex->GetView());


    // Bind vertex and index buffers
    Uint32   offset = 0;
    IBuffer* pBuffs[] = { vb1->GetVBuf()  };
    devCon->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    devCon->SetIndexBuffer(vb1->GetIBuf(), 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    // Set the pipeline state
    devCon->SetPipelineState(ren->GetState());
    // Commit shader resources. RESOURCE_STATE_TRANSITION_MODE_TRANSITION mode
    // makes sure that resources are transitioned to required states.
    devCon->CommitShaderResources(ren->GetBinding(), RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    DrawIndexedAttribs DrawAttrs;     // This is an indexed draw call
    DrawAttrs.IndexType = VT_UINT32; // Index type
    DrawAttrs.NumIndices = 12;
    // Verify the state of vertex and index buffers
    DrawAttrs.Flags = DRAW_FLAG_VERIFY_ALL;
    devCon->DrawIndexed(DrawAttrs);


};

