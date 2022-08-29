#pragma once
#include<map>
#include<string>
#include"Shader.h"
namespace Engine::Core::GraphicsCon {
    class ShaderManager
    {
    public:
        void SetShaderPass();


    private:
        std::map<std::string, Shader> ShaderList;


    };
}
