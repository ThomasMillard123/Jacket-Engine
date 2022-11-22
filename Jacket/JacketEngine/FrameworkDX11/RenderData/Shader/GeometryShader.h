#pragma once
#include"Shader.h"
namespace Engine::Core::Graphics {
    class GeometryShader : public Shader
    {
    public:
        GeometryShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        ~GeometryShader();
        HRESULT CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        void CleanUp();
    private:
        ID3D11GeometryShader* _pGeometryShader;
    };

}