#pragma once
#include<Windows.h>
#include<string>
#include "resource.h"

namespace Engine::Core::WindowCon {
    class WindowContainer
    {
    public:
        WindowContainer( HINSTANCE hInstance,  int nCmdShow, int width, int hight, std::string windowTitle, std::string windowClass);
        ~WindowContainer();
       
        HINSTANCE GetHInst() { return _HInst; }
        HWND GetHWnd() { return _HWnd; }
    private:
        //newWindow
        bool InitWindow( HINSTANCE hInstance,  int nCmdShow);
        bool RegisterWindowClass(HINSTANCE hInstance);

    private:

       
        UINT _WindowWidth;
        UINT _WindowHight;

        std::wstring _WindowTitle;
        std::wstring _WindowClass;

        HINSTANCE  _HInst;
        HWND _HWnd;

        bool _IsDestoryed;
    };

}