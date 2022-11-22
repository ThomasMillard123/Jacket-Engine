#pragma once
#include"Shader.h"
namespace Engine::Core::Graphics {
    class DomianShader : public Shader
    {
    public:
        DomianShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        ~DomianShader();
        HRESULT CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        void CleanUp();

    private:
        ID3D11DomainShader* _pDomainShader;
    };

}