#pragma once

#include"windowCon.h"
#include"RenderData/Graphics.h"
namespace Engine::Core 
{
   
    /// <summary>
    /// Controll point of main engein
    /// </summary>
    class EngineClass
    {
    public:
        bool InitEngine( HINSTANCE hInstance, int nCmdShow,int width, int Hight, std::string WindowTitle, std::string WindowClass);
        static EngineClass* Instance();

        bool ProcessMessages();
        
        void Update();
        void Draw();
        
    private:
        EngineClass(){}
        ~EngineClass();


    private:
        HINSTANCE _HInstance;
        Engine::Core::WindowCon::WindowContainer* _Window;
    };
   
}

