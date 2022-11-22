#pragma once
#include"Shader.h"
namespace Engine::Core::Graphics {
    class HullShader : public Shader
    {
    public:
        HullShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        ~HullShader();
        HRESULT CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        void CleanUp();

    private:
        ID3D11HullShader* _pHullShader;
    };

}