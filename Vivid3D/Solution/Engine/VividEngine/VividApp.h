#pragma once

#include "pch.h"
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

using namespace Diligent;

namespace Vivid {

    namespace App {

        class VividApp
        {
        public:

            VividApp();

            static void SetPath(const char* path)
            {

                AppPath = path;

            }

            static const char* GetPath()
            {

                return AppPath;

            }

            static const char* GetResPath(const char* path) {

                auto r =  std::string(AppPath) + std::string(path);
                
                int siz = r.length() + 1;

                const char* ns = r.c_str();

                char* rs = new char[siz];
                for (int i = 0; i < siz; i++) {

                    rs[i] = ns[i];

                }
                rs[siz - 1] = 0;

                
                return rs;


            }

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

            static RefCntAutoPtr<IDeviceContext> GetDeviceContext() {

                return sThis->m_pImmediateContext;

            }

        private:
            static Vivid::App::VividApp *sThis;
            int winWidth, winHeight;
            static const char* AppPath;
            RefCntAutoPtr<IEngineFactory> m_pEngineFactory;
            RefCntAutoPtr<IRenderDevice>  m_pDevice;
            RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
            RefCntAutoPtr<ISwapChain>     m_pSwapChain;
            RefCntAutoPtr<IPipelineState> m_pPSO;
            RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
        };


    }

}