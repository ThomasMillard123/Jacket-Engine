#pragma once
#include"Shader.h"
namespace Engine::Core::GraphicsCon {
    class DomianShader : public Shader
    {
    public:
        HRESULT CreatDomianShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);


    private:
        ID3D11DomainShader* _pDomainShader;
    };

}