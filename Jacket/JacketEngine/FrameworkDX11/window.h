#pragma once
#include<Windows.h>
#include<string>
#include "resource.h"

namespace Engine::Core::Window {
    class WindowClass
    {
    public:
        WindowClass(_In_ HINSTANCE hInstance, _In_ int nCmdShow, int width, int hight, std::string windowTitle);
        ~WindowClass();
       
       
    private:
        bool InitWindow(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
        bool RegisterWindowClass(HINSTANCE hInstance);

    private:

       
        UINT _WindowWidth;
        UINT _WindowHight;

        std::string _WindowTitle;
        HINSTANCE  _HInst;
        HWND _HWnd;
    };

}