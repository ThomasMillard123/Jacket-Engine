#include "TextureManager.h"
namespace Engine::RenderObject {
    TextureManager* TextureManager::Instance()
    {
        static TextureManager TXManager;
        return &TXManager;
    }
}