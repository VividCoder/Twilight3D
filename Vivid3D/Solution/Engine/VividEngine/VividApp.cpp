#include "pch.h"
#include "VividApp.h"

using namespace Vivid::App;

static const char* VSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};

void main(in  uint    VertId : SV_VertexID,
          out PSInput PSIn) 
{
    float4 Pos[3];
    Pos[0] = float4(-0.5, -0.5, 0.0, 1.0);
    Pos[1] = float4( 0.0, +0.5, 0.0, 1.0);
    Pos[2] = float4(+0.5, -0.5, 0.0, 1.0);

    float3 Col[3];
    Col[0] = float3(1.0, 0.0, 0.0); // red
    Col[1] = float3(0.0, 1.0, 0.0); // green
    Col[2] = float3(0.0, 0.0, 1.0); // blue

    PSIn.Pos   = Pos[VertId];
    PSIn.Color = Col[VertId];
}
)";

// Pixel shader simply outputs interpolated vertex color
static const char* PSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};

struct PSOutput
{ 
    float4 Color : SV_TARGET; 
};

void main(in  PSInput  PSIn,
          out PSOutput PSOut)
{
    PSOut.Color = float4(PSIn.Color.rgb, 1.0);
}
)";



void VividApp::WindowResize(int w, int h)
{

    if (m_pSwapChain)
        m_pSwapChain->Resize(w, h);

    winWidth = w;
    winHeight = h;

}

VividApp::VividApp() {

    sThis = this;

}

VividApp * VividApp::sThis = NULL;



bool VividApp::InitBackend(HWND hWnd) {

    SwapChainDesc SCDesc;
    switch (m_DeviceType)
    {
#if D3D11_SUPPORTED
    case RENDER_DEVICE_TYPE_D3D11:
    {
        EngineD3D11CreateInfo EngineCI;
#    ifdef DILIGENT_DEBUG
        EngineCI.DebugFlags |=
            D3D11_DEBUG_FLAG_CREATE_DEBUG_DEVICE |
            D3D11_DEBUG_FLAG_VERIFY_COMMITTED_SHADER_RESOURCES;
#    endif
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D11() function
        auto GetEngineFactoryD3D11 = LoadGraphicsEngineD3D11();
#    endif
        auto* pFactoryD3D11 = GetEngineFactoryD3D11();
        pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
        Win32NativeWindow Window{ hWnd };
        pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
    }
    break;
#endif


#if D3D12_SUPPORTED
    case RENDER_DEVICE_TYPE_D3D12:
    {
#    if ENGINE_DLL
        // Load the dll and import GetEngineFactoryD3D12() function
        auto GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
#    endif
        EngineD3D12CreateInfo EngineCI;
#    ifdef DILIGENT_DEBUG
        // There is a bug in D3D12 debug layer that causes memory leaks in this tutorial
        //EngineCI.EnableDebugLayer = true;
#    endif
        auto* pFactoryD3D12 = GetEngineFactoryD3D12();
        m_pEngineFactory = pFactoryD3D12;
        pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
        Win32NativeWindow Window{ hWnd };
        pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
    }
    break;
#endif


#if GL_SUPPORTED
    case RENDER_DEVICE_TYPE_GL:
    {

#    if EXPLICITLY_LOAD_ENGINE_GL_DLL
        // Load the dll and import GetEngineFactoryOpenGL() function
        auto GetEngineFactoryOpenGL = LoadGraphicsEngineOpenGL();
#    endif
        auto* pFactoryOpenGL = GetEngineFactoryOpenGL();

        EngineGLCreateInfo EngineCI;
        EngineCI.Window.hWnd = hWnd;
        pFactoryOpenGL->CreateDeviceAndSwapChainGL(EngineCI, &m_pDevice, &m_pImmediateContext, SCDesc, &m_pSwapChain);
    }
    break;
#endif


#if VULKAN_SUPPORTED
    case RENDER_DEVICE_TYPE_VULKAN:
    {
#    if EXPLICITLY_LOAD_ENGINE_VK_DLL
        // Load the dll and import GetEngineFactoryVk() function
        auto GetEngineFactoryVk = LoadGraphicsEngineVk();
#    endif
        EngineVkCreateInfo EngineCI;
#    ifdef DILIGENT_DEBUG
        EngineCI.EnableValidation = true;
#    endif
        auto* pFactoryVk = GetEngineFactoryVk();
        pFactoryVk->CreateDeviceAndContextsVk(EngineCI, &m_pDevice, &m_pImmediateContext);

        if (!m_pSwapChain && hWnd != nullptr)
        {
            Win32NativeWindow Window{ hWnd };
            pFactoryVk->CreateSwapChainVk(m_pDevice, m_pImmediateContext, SCDesc, Window, &m_pSwapChain);
        }
    }
    break;
#endif


    default:
        std::cerr << "Unknown/unsupported device type";
        return false;
        break;
    }

    return true;

}

void VividApp::CreateResources() {


    PipelineStateCreateInfo PSOCreateInfo;
    PipelineStateDesc& PSODesc = PSOCreateInfo.PSODesc;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSODesc.Name = "Simple triangle PSO";

    // This is a graphics pipeline
    PSODesc.IsComputePipeline = false;

    // clang-format off
    // This tutorial will render to a single render target
    PSODesc.GraphicsPipeline.NumRenderTargets = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSODesc.GraphicsPipeline.RTVFormats[0] = m_pSwapChain->GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    PSODesc.GraphicsPipeline.DSVFormat = m_pSwapChain->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSODesc.GraphicsPipeline.PrimitiveTopology = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // No back face culling for this tutorial
    PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = CULL_MODE_NONE;
    // Disable depth testing
    PSODesc.GraphicsPipeline.DepthStencilDesc.DepthEnable = False;
    // clang-format on

    ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.UseCombinedTextureSamplers = true;
    // Create a vertex shader
    RefCntAutoPtr<IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Triangle vertex shader";
        ShaderCI.Source = VSSource;
        m_pDevice->CreateShader(ShaderCI, &pVS);
    }

    // Create a pixel shader
    RefCntAutoPtr<IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Triangle pixel shader";
        ShaderCI.Source = PSSource;
        m_pDevice->CreateShader(ShaderCI, &pPS);
    }

    // Finally, create the pipeline state
    PSODesc.GraphicsPipeline.pVS = pVS;
    PSODesc.GraphicsPipeline.pPS = pPS;
    m_pDevice->CreatePipelineState(PSOCreateInfo, &m_pPSO);

    InitApp();


};

bool VividApp::ProcessCommandLine(const char* CmdLine)
{

    const auto* Key = "-mode ";
    const auto* pos = strstr(CmdLine, Key);
    if (pos != nullptr)
    {
        pos += strlen(Key);
        if (_stricmp(pos, "D3D11") == 0)
        {
#if D3D11_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
#else
            std::cerr << "Direct3D11 is not supported. Please select another device type";
            return false;
#endif
        }
        else if (_stricmp(pos, "D3D12") == 0)
        {
#if D3D12_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
#else
            std::cerr << "Direct3D12 is not supported. Please select another device type";
            return false;
#endif
        }
        else if (_stricmp(pos, "GL") == 0)
        {
#if GL_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_GL;
#else
            std::cerr << "OpenGL is not supported. Please select another device type";
            return false;
#endif
        }
        else if (_stricmp(pos, "VK") == 0)
        {
#if VULKAN_SUPPORTED
            m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
#else
            std::cerr << "Vulkan is not supported. Please select another device type";
            return false;
#endif
        }
        else
        {
            std::cerr << "Unknown device type. Only the following types are supported: D3D11, D3D12, GL, VK";
            return false;
        }
    }
    else
    {
#if D3D12_SUPPORTED
        m_DeviceType = RENDER_DEVICE_TYPE_D3D12;
#elif VULKAN_SUPPORTED
        m_DeviceType = RENDER_DEVICE_TYPE_VULKAN;
#elif D3D11_SUPPORTED
        m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
#elif GL_SUPPORTED
        m_DeviceType = RENDER_DEVICE_TYPE_GL;
#endif
    }
    return true;

}

void VividApp::Present()
{
    m_pSwapChain->Present();
}


void VividApp::Render() {

    UpdateApp();


    // Set render targets before issuing any draw command.
       // Note that Present() unbinds the back buffer if it is set as render target.
    auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
    auto* pDSV = m_pSwapChain->GetDepthBufferDSV();
    m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    // Clear the back buffer
    const float ClearColor[] = { 0.350f, 0.350f, 0.350f, 1.0f };
    // Let the engine perform required state transitions
    m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

   

    RenderApp();


}

const char* Vivid::App::VividApp::AppPath = NULL;