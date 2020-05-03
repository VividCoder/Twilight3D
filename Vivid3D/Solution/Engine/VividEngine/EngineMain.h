#pragma once

#include "pch.h"
#include "VividApp.h"
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
            switch (message)
            {
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



        bool initWindow(HINSTANCE hInstance, int nCmdShow, VividApp* app)
        {

            g_pTheApp.reset(app);


            const auto* cmdLine = GetCommandLineA();
            if (!g_pTheApp->ProcessCommandLine(cmdLine))
                return -1;


            std::wstring Title(L"VividEngine: Sample:Simple1");
            switch (g_pTheApp->GetDeviceType())
            {
            case RENDER_DEVICE_TYPE_D3D11: Title.append(L" (D3D11)"); break;
            case RENDER_DEVICE_TYPE_D3D12: Title.append(L" (D3D12)"); break;
            case RENDER_DEVICE_TYPE_GL: Title.append(L" (GL)"); break;
            case RENDER_DEVICE_TYPE_VULKAN: Title.append(L" (VK)"); break;
            }
            // Register our window class
            WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, MessageProc,
                               0L, 0L, hInstance, NULL, NULL, NULL, NULL, L"SampleApp", NULL };
            RegisterClassEx(&wcex);

            // Create a window
            LONG WindowWidth = 800;
            LONG WindowHeight = 600;
            RECT rc = { 0, 0, WindowWidth, WindowHeight };
            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
            HWND wnd = CreateWindow(L"SampleApp", Title.c_str(),
                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
            if (!wnd)
            {
                MessageBox(NULL, L"Cannot create window", L"Error", MB_OK | MB_ICONERROR);
                return 0;
            }
            ShowWindow(wnd, nCmdShow);
            UpdateWindow(wnd);


            if (!g_pTheApp->InitBackend(wnd))
                return -1;

            g_pTheApp->CreateResources();

            // Main message loop
            MSG msg = { 0 };
            while (WM_QUIT != msg.message)
            {
                if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                {
                    g_pTheApp->Render();
                    g_pTheApp->Present();
                    printf("Ye!");

                }
            }

            g_pTheApp.reset();


            return (int)msg.wParam;

        }

        int vInitEngine()
        {
            printf("Initializing VivdEngine.");

            return 1;
        }
    }
}