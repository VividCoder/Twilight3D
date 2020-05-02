#pragma once

#include "pch.h"

using namespace Diligent;



class VividApp
{
public:

	void WindowResize(int w, int h);
    bool InitBackend(HWND hWnd);

    bool ProcessCommandLine(const char* CmdLine);

    void Present();

    void CreateResources();

    void Render();

    virtual void InitApp() {};
    virtual void UpdateApp() {};
    virtual void RenderApp() {};
    virtual void CloseApp() {};
     
    RENDER_DEVICE_TYPE GetDeviceType() const { return m_DeviceType; }

private:
    int winWidth, winHeight;
    RefCntAutoPtr<IRenderDevice>  m_pDevice;
    RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
    RefCntAutoPtr<ISwapChain>     m_pSwapChain;
    RefCntAutoPtr<IPipelineState> m_pPSO;
    RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
};

