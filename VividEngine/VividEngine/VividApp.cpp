#include "pch.h"
#include "VividApp.h"

void VividApp::WindowResize(int w, int h)
{

    if (m_pSwapChain)
        m_pSwapChain->Resize(w, h);

    winWidth = w;
    winHeight = h;

}

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