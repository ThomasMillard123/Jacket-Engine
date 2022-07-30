#include "Engine.h"

bool Engine::Core::EngineClass::InitEngine(HINSTANCE hInstance, int nCmdShow, std::string WindowTitle, std::string WindowClass)
{
    if (FAILED(InitWindow(hInstance, nCmdShow)))
        return 0;

    if (FAILED(InitDevice()))
    {
        Cleanup();
        return 0;
    }

   

    return S_OK;
    return false;
}
