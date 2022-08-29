#pragma once
#include"Shader.h"
namespace Engine::Core::GraphicsCon {
    class GeometryShader : public Shader
    {
    public:
        GeometryShader();
        GeometryShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        ~GeometryShader();
        HRESULT CreatGeometryShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
    private:
        ID3D11GeometryShader* _pGeometryShader;
    
    };

}