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
            static std::string rp;
            static std::string imp_path;
            static const char* ImpPath; 
            static void SetPath(const char* path)
            {

                rp = std::string(path);
                AppPath = rp.c_str();

            }
            
            static void SetImpPath(const char* path) {

                imp_path = std::string(path);
                ImpPath = imp_path.c_str();

            }
          
            static const char* GetImpPath(const char *path) {

                auto r = std::string(imp_path) + std::string(path);

                int siz = r.length() + 1;

                const char* ns = r.c_str();

                char* rs = new char[siz];
                for (int i = 0; i < siz; i++) {

                    rs[i] = ns[i];

                }
                rs[siz - 1] = 0;


                return rs;
            }
            static const char* GetPath()
            {

                return AppPath;

            }

            static const char* GetResPath(const char* path) {


                printf("ResCr:");
                printf(path);
                printf("\n");

                printf("App:");
                printf(AppPath);
                printf("\n");

                auto r =  std::string(AppPath) + std::string(path);
                
                int siz = r.length() + 1;

                const char* ns = r.c_str();

                char* rs = new char[siz];
                for (int i = 0; i < siz; i++) {

                    rs[i] = ns[i];

                }
                rs[siz - 1] = 0;

                printf("ResourcePath:");
                printf(rs);
                printf("!\n");
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

            static void SetMouse(int x, int y) {

                int lx, ly;
                lx = MouseX;
                ly = MouseY;
                MouseX = x;
                MouseY = y;

                if (firstMouse) {
                   
                    MouseDX = 0;
                    MouseDY = 0;
                    firstMouse = false;

                }
                else {
                    MouseDX = MouseX - lx;
                    MouseDY = MouseY - ly;
                }

            }

            static int GetMouseX() {
                return MouseX;
            }

            static int GetMouseY() {
                return MouseY;
            }

            static int GetMouseDX() {
                return MouseDX;
            }

            static int GetMouseDY() {
                return MouseDY;
            }

            static void CallMouseMoveFunc(int x, int y) {

                sThis->MouseMoved(x, y);

            }

        

            static void CallKeyDown(int key) {


                sThis->SetKeyDown(key);
                //sThis->KeyDown(int key);

            }

            static void CallKeyUp(int key) {

                sThis->SetKeyDown(key);

            };

            static void SetSize(int w, int h) {

                WinW = w;
                WinH = h;

            }

            static int GetW() {

                return WinW;

            }

            static int GetH() {

                return WinH;

            }


            virtual void MouseMoved(int x, int y) {};
            virtual void SetKeyDown(int k) {};
            virtual void SetKeyUp(int k) {};
private:

         //   static void (*FMouseMove)(int, int) = NULL;

    static int WinW, WinH;

            static int MouseX, MouseY;
            static int MouseDX, MouseDY;
            static bool firstMouse;

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