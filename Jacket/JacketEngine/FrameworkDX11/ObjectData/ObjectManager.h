#pragma once
#include<map>
#include"RenderObject/Object.h"
namespace Engine::RenderObject {
    class ObjectManager
    {
    public:
        static ObjectManager* Instance();
        void Update(float dT);
        void Draw();
        void CleanUp();
    private:
        ObjectManager() {}
        ~ObjectManager() {}

    private:
        std::map<std::string, Object*> ObjectMap;
    };


}
