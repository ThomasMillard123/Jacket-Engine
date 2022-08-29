#pragma once
#include<map>
#include"Textures/Texture.h"

namespace Engine::RenderObject {
    /// <summary>
    /// Texture Resource manager
    /// </summary>
    class TextureManager
    {
    public:
        static TextureManager* Instance();

        bool LoadTexture(std::string FileName);
        Texture* GetTexture(std::string Name);

        bool UnloadTexture(std::string Name);
        bool UnloadAllTexture();
    private:
        TextureManager() {};
        ~TextureManager() {};
    private:
        std::map<std::string, Texture*> TextureMap;

    };

}