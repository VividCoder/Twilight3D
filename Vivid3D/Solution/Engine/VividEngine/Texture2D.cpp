#include "pch.h"
#include "Texture2D.h"
//#include "Graphics/GraphicsTools/interface//i"


//#include "IL/ilut.h


#define _CRT_SECURE_NO_WARNINGS



using namespace Vivid::Texture;
using namespace Diligent;

const wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

Texture2D::Texture2D(void* data, int w, int h,int bpp) {

    printf("tex2d\n");
    TextureDesc TexDesc;
    TexDesc.Name = "";

    TexDesc.Type = RESOURCE_DIM_TEX_2D;
    TexDesc.Width = w;
    TexDesc.Height = h;
    TexDesc.Format = TEX_FORMAT_RGBA8_UNORM;
    TexDesc.Usage = USAGE_DEFAULT;
    TexDesc.BindFlags = BIND_SHADER_RESOURCE | BIND_RENDER_TARGET | BIND_UNORDERED_ACCESS;
    //TexDesc.Name = "Sample 2D Texture";
    printf("descdone\n");

    auto dev = Vivid::App::VividApp::GetDevice();

    TextureSubResData sub;
    printf("got details\n");

    sub.pData = data;
    sub.Stride = w * bpp;
    printf("set data\n");
    printf("w:%d h:%d", w, h);
    printf("bpp:%d", bpp);
    printf("\n");
    TextureData dat;
    dat.pSubResources = &sub;
    dat.NumSubresources = 1;

    printf("Creating tex.\n");

    dev->CreateTexture(TexDesc, &dat, &tex);
    printf("Created\n");
    texView = tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
    printf("Got tex view.\n");


};

//Texture2D::Texture2D()


Texture2D::Texture2D(const char* path,bool useImp) {

    const char* realPath;
        

    if (useImp) {
        realPath = Vivid::App::VividApp::GetImpPath(path);
    }else{
       realPath = Vivid::App::VividApp::GetResPath(path);
    }
   // DBOUT("TexPath:" << realPath << "\n");
    path = realPath;

    printf("real:");
    printf(realPath);
    printf("----\n");

    std::vector<unsigned char> img;
    unsigned iw, ih;
    unsigned error = lodepng::decode(img, iw, ih, path);

    if (error != 0) {
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
        return;
    }

    std::cout << "Loaded image. W:" << iw << " H:" << ih << std::endl;


    auto nt = new Texture2D(&img[0],iw,ih,4);

    printf("Loaded\n");

    tex = nt->GetTex();
    texView = nt->GetView();

    texpath = path;
    printf("Done.\n");
    
    /*
    TextureLoadInfo loadInfo;
    loadInfo.IsSRGB = true;
    RefCntAutoPtr<ITexture> Tex;
    CreateTextureFromFile(path, loadInfo,Vivid::App::VividApp::GetDevice(), &Tex);
    tex = Tex;
    // Get shader resource view from the texture
    texView = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
    DBOUT("Tex:" << path);
    texpath = path;
    */
    // Set texture SRV in the SRBr
  //  m_SRB->GetVariableByName(SHADER_TYPE_PIXEL, "g_Texture")->Set(m_TextureSRV);
}