#pragma once
#include"Shader.h"
namespace Engine::Core::GraphicsCon {
    class PixleShader: public Shader
    {
    public:
        HRESULT CreatPixleShader(WCHAR* szFileName, ID3D11Device* pd3dDevice);
    private:
        ID3D11PixelShader* _pPixelShader;
    };

}