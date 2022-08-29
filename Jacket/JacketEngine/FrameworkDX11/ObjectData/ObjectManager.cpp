#include "ObjectManager.h"
namespace Engine::RenderObject {
    ObjectManager* Engine::RenderObject::ObjectManager::Instance()
    {
        static ObjectManager ObjectInst;
        return &ObjectInst;
    }
    void ObjectManager::Update(float dT)
    {
    }
    void ObjectManager::Draw()
    {
    }
}