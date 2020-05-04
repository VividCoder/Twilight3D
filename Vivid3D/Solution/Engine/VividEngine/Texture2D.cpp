#include "pch.h"
#include "Texture2D.h"
//#include "Graphics/GraphicsTools/interface//i"


using namespace Vivid::Texture;
using namespace Diligent;

Texture2D::Texture2D(const char* path) {

	const char* realPath = Vivid::App::VividApp::GetResPath(path);

   // DBOUT("TexPath:" << realPath << "\n");

    TextureLoadInfo loadInfo;
    loadInfo.IsSRGB = true;
    RefCntAutoPtr<ITexture> Tex;
    CreateTextureFromFile(realPath, loadInfo,Vivid::App::VividApp::GetDevice(), &Tex);
    tex = Tex;
    // Get shader resource view from the texture
    texView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
    DBOUT("Tex:" << realPath);
    texpath = realPath;
    // Set texture SRV in the SRB
  //  m_SRB->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Set(m_TextureSRV);
}