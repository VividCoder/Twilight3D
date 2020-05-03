#include "pch.h"
#include "RenderState2D.h"

using namespace Vivid::RenderState;
using namespace Diligent;

RenderState2D::RenderState2D() {

    RefCntAutoPtr<IRenderDevice> device = Vivid::App::VividApp::GetDevice();
    RefCntAutoPtr<ISwapChain> swapChain = Vivid::App::VividApp::GetSwapChain();
    RefCntAutoPtr<IEngineFactory> engineFactory = Vivid::App::VividApp::GetEngineFactory();

    PipelineStateCreateInfo PSOCreateInfo;
    PipelineStateDesc& PSODesc = PSOCreateInfo.PSODesc;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSODesc.Name = "RenderState2D";

    // This is a graphics pipeline
    PSODesc.IsComputePipeline = false;

    // clang-format off
    // This tutorial will render to a single render target
    PSODesc.GraphicsPipeline.NumRenderTargets = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSODesc.GraphicsPipeline.RTVFormats[0] = swapChain->GetDesc().ColorBufferFormat;
    // Set depth buffer format which is the format of the swap chain's back buffer
    PSODesc.GraphicsPipeline.DSVFormat = swapChain->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSODesc.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // Cull back faces
    PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_BACK;
    // Enable depth testing
    PSODesc.GraphicsPipeline.DepthStencilDesc.DepthEnable = True;
    // clang-format on

    ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood.
    ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.UseCombinedTextureSamplers = true;

    // In this tutorial, we will load shaders from file. To be able to do that,
    // we need to create a shader source stream factory
    RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;
    engineFactory->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;
    // Create a vertex shader
    RefCntAutoPtr<IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Cube VS";
        ShaderCI.FilePath = Vivid::App::VividApp::GetResPath("render2D.vsh");
        device->CreateShader(ShaderCI, &pVS);
        // Create dynamic uniform buffer that will store our transformation matrix
        // Dynamic buffers can be frequently updated by the CPU
        BufferDesc CBDesc;
        CBDesc.Name = "VS constants CB";
        CBDesc.uiSizeInBytes = sizeof(Diligent::float4x4);
        CBDesc.Usage = USAGE_DYNAMIC;
        CBDesc.BindFlags = BIND_UNIFORM_BUFFER;
        CBDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
        device->CreateBuffer(CBDesc, nullptr, &vsConsts);
    }

    // Create a pixel shader
    RefCntAutoPtr<IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Cube PS";
        ShaderCI.FilePath = Vivid::App::VividApp::GetResPath("Render2D.psh");
        device->CreateShader(ShaderCI, &pPS);
    }

    // clang-format off
    // Define vertex shader input layout
    LayoutElement LayoutElems[] =
    {
        // Attribute 0 - vertex position
        LayoutElement{0, 0, 3, VT_FLOAT32, False},
        // Attribute 1 - vertex color
        LayoutElement{1, 0, 4, VT_FLOAT32, False},
        LayoutElement{2,0,2,VT_FLOAT32,False }
    };
    // clang-format on
    PSODesc.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems;
    PSODesc.GraphicsPipeline.InputLayout.NumElements = _countof(LayoutElems);

    PSODesc.GraphicsPipeline.pVS = pVS;
    PSODesc.GraphicsPipeline.pPS = pPS;

    // Define variable type that will be used by default
    PSODesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;


    // Since we did not explcitly specify the type for 'Constants' variable, default
    // type (SHADER_RESOURCE_VARIABLE_TYPE_STATIC) will be used. Static variables never
    // change and are bound directly through the pipeline state object.

    ShaderResourceVariableDesc Vars[] =
    {
        {SHADER_TYPE_PIXEL, "g_Texture", SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
    };
    PSODesc.ResourceLayout.Variables = Vars;
    PSODesc.ResourceLayout.NumVariables = _countof(Vars);


    SamplerDesc SamLinearClampDesc
    {
        FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR, FILTER_TYPE_LINEAR,
        TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP, TEXTURE_ADDRESS_CLAMP
    };
    StaticSamplerDesc StaticSamplers[] =
    {
        {SHADER_TYPE_PIXEL, "g_Texture", SamLinearClampDesc}
    };

    PSODesc.ResourceLayout.StaticSamplers = StaticSamplers;
    PSODesc.ResourceLayout.NumStaticSamplers = _countof(StaticSamplers);


    device->CreatePipelineState(PSOCreateInfo, &pState);


    pState->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(vsConsts);

    // Create a shader resource binding object and bind all static resources in it
    pState->CreateShaderResourceBinding(&pRB, true);

};