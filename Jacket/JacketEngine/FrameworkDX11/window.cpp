#include "window.h"

namespace Engine::Core::Window {
    LRESULT CALLBACK WindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

        switch (message)
        {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            return 0;

            // Handle all other messages
        default:
        {
            //Get ptr to window class

           // Forward messages to window class
            //return app->WndProc(hWnd, message, wParam, lParam);
        }



        }
    }
    WindowClass::WindowClass(HINSTANCE hInstance, int nCmdShow, int width, int hight, std::string windowTitle):
        _WindowWidth(width),
        _WindowHight(hight),
        _WindowTitle(windowTitle)
    {
        InitWindow(hInstance, nCmdShow);
    }
    WindowClass::~WindowClass()
    {
    }
    bool WindowClass::InitWindow(HINSTANCE hInstance, int nCmdShow )
    {
       
        if (!RegisterWindowClass(hInstance)) {
            return E_FAIL;
        }
        // Create window
        _HInst = hInstance;
        RECT rc = { 0, 0, _WindowWidth, _WindowHight };



        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
        _HWnd = CreateWindow(_WindowTitle, L"Direct3D 11",
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
            nullptr);
        if (!_HWnd)
            return E_FAIL;

        ShowWindow(_HWnd, nCmdShow);


        RAWINPUTDEVICE rid;
        rid.usUsagePage = 0x01;
        rid.usUsage = 0x02;
        rid.hwndTarget = NULL;
        rid.dwFlags = 0;

        if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == false) {
            return E_FAIL;
        }


        return S_OK;

    }
    bool WindowClass::RegisterWindowClass(HINSTANCE hInstance)
    {
        // Register class
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WindProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = L"TutorialWindowClass";
        wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
        if (!RegisterClassEx(&wcex))
            return E_FAIL;
        return S_OK;
    }
  
}