#pragma once
#include <d3d11_1.h>
#include<string>


namespace Engine::RenderObject {
    class Texture
    {
        Texture();
        //Texture();

        ~Texture();

        bool Load(std::string File);
        bool Unload();
    private:
        std::string _TextureName;
        ID3D11ShaderResourceView* _pShaderResource;

    };

}