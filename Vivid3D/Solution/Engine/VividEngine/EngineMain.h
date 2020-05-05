#pragma once

#include "pch.h"
#include "VividApp.h"
#include "windowsx.h"

#if PLATFORM_MACOS
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#if PLATFORM_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include "GLFW/glfw3native.h"

using namespace Diligent;


namespace Vivid {

    namespace Engine {

        RefCntAutoPtr<IRenderDevice>  m_pDevice;
        RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
        RefCntAutoPtr<ISwapChain>     m_pSwapChain;
        RefCntAutoPtr<IPipelineState> m_pPSO;
        RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D11;
        std::unique_ptr<VividApp> g_pTheApp;




        // Called every time the NativeNativeAppBase receives a message
        LRESULT CALLBACK MessageProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            int xPos, yPos;
            xPos = yPos = 0;
            switch (message)
            {
           
            case WM_MOUSEMOVE:
                 xPos = GET_X_LPARAM(lParam);
                 yPos = GET_Y_LPARAM(lParam);
                 VividApp::CallMouseMoveFunc(xPos, yPos);
                return 0;
            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                BeginPaint(wnd, &ps);
                EndPaint(wnd, &ps);
                return 0;
            }
            case WM_SIZE: // Window size has been changed
                if (g_pTheApp)
                {
                    g_pTheApp->WindowResize((int)LOWORD(lParam), (int)HIWORD(lParam));
                }
                return 0;

            case WM_KEYDOWN:
                VividApp::CallKeyDown((int)wParam);
                return 0;
            case WM_CHAR:
                if (wParam == VK_ESCAPE)
                    PostQuitMessage(0);
                return 0;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

                lpMMI->ptMinTrackSize.x = 320;
                lpMMI->ptMinTrackSize.y = 240;
                return 0;
            }

            default:
                return DefWindowProc(wnd, message, wParam, lParam);
            }
        }



        bool initWindow(VividApp* app)
        {

            g_pTheApp.reset(app);


            GLFWwindow* window;

            /* Initialize the library */
            if (!glfwInit()) {
                return -1;
            }

#if PLATFORM_WIN32
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

            /* Create a windowed mode window and its OpenGL context */
            window = glfwCreateWindow(800, 600, "Vivid3D Application", NULL, NULL);

            if (!window) {
                glfwTerminate();
                return -1;
            }
     
            HWND hw;
            void* window_handle = NULL;
#if PLATFORM_WIN32
            hw = glfwGetWin32Window(window);
#elif PLATFORM_MACOS
            glfwMakeContextCurrent(window);
            window_handle = static_cast<void*>(glfwGetCocoaWindow(window));
#elif PLATFORM_LINUX
            // FIXME: Get x11 or wayland window handle using glfw
            glfwMakeContextCurrent(window);
            throw std::runtime_error("Missing window handle");
#endif


           if (!g_pTheApp->InitBackend(hw))
               return -1;


            g_pTheApp->CreateResources();

          
            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window)) {
                //if (m_pImmediateContext) {

               

                    g_pTheApp->Render();

#if PLATFORM_MACOS
                    glfwSwapBuffers(window);
#else
                    g_pTheApp->Present();
#endif
                

                /* Poll for and process events */
                glfwPollEvents();
            }
          
            glfwTerminate();
        }

        int vInitEngine()
        {
            printf("Initializing VivdEngine.");

            return 1;
        }
    }
}