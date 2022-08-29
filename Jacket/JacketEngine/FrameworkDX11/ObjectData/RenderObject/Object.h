#pragma once
#include<string>
namespace Engine::RenderObject {
    class Object
    {
    public:
        Object() {}
        ~Object() {}

        virtual bool LoadObject() {};
    protected:
        std::string ObjectName;
        std::string FileName;

    };

}