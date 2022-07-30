#pragma once


namespace Engine::Core 
{
   
    /// <summary>
    /// Controll point of main engein
    /// </summary>

    #include"window.h"
    class EngineClass
    {
    public:
        bool InitEngine(_In_ HINSTANCE hInstance, _In_ int nCmdShow, std::string WindowTitle, std::string WindowClass);
        EngineClass* Instance();

    private:
        EngineClass();
        ~EngineClass();


    };
   
}

