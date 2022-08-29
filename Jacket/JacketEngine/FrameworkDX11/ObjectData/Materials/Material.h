#pragma once
#include"../TextureManager.h"

//https://learnopengl.com/PBR/Theory

namespace Engine::RenderObject {
    class Material
    {
    public:
        Material();
        //Material();
    private:
        std::string Name;

        //all textuers
     /*   ID3D11ShaderResourceView* _Albedo;
        ID3D11ShaderResourceView* _Roughness;
        ID3D11ShaderResourceView* _Normal;
        ID3D11ShaderResourceView* _AmbiantOcclusion;
        ID3D11ShaderResourceView* _Metallic;
        ID3D11ShaderResourceView* _Emission;*/
    };

}