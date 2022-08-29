

#include <windows.h>
#include <tchar.h>
#include"Engine.h"

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
) 
{
    
        UNREFERENCED_PARAMETER(hPrevInstance);
        UNREFERENCED_PARAMETER(lpCmdLine);
        
        //Load Egine
        if (!Engine::Core::EngineClass::Instance()->InitEngine(hInstance, nCmdShow,2000,1000, "window", "TutorialWindowClass")) {
            return 0;
        }
       
        //Load Data and objects

        while (Engine::Core::EngineClass::Instance()->ProcessMessages())
        {
            //do something



            Engine::Core::EngineClass::Instance()->Update();
            Engine::Core::EngineClass::Instance()->Draw();
        }

        return 0;

}


