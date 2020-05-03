#pragma once

#include "pch.h"

using namespace Diligent;

namespace Vivid {

    namespace App {

        class VividApp
        {
        public:

            VividApp();

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

            static RefCntAutoPtr<IRenderDevice> GetDevice()
            {
                return sThis->m_pDevice;
            }

            static RefCntAutoPtr<ISwapChain> GetSwapChain()
            {
                return sThis->m_pSwapChain;
            }

            static RefCntAutoPtr<IEngineFactory> GetEngineFactory() {

                return sThis->m_pEngineFactory;

            };

        private:
            static Vivid::App::VividApp *sThis;
            int winWidth, winHeight;
            RefCntAutoPtr<IEngineFactory> m_pEngineFactory;
            RefCntAutoPtr<IRenderDevice>  m_pDevice;
            RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
            RefCntAutoPtr<ISwapChain>     m_pSwapChain;
            RefCntAutoPtr<IPipelineState> m_pPSO;
            RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
        };


    }

}