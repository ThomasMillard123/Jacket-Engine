#pragma once
#include"Shader.h"
namespace Engine::Core::GraphicsCon {
    class HullShader : public Shader
    {
    public:
        HRESULT CreatHullShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        ID3D11HullShader* _pHullShader;
    };

}