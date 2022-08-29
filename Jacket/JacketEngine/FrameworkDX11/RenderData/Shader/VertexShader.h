#pragma once
#include<vector>

#include"Shader.h"
namespace Engine::Core::GraphicsCon {
    class VertexShader : public Shader
    {
    public:

        HRESULT CreatVertexShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout);
        
    private:
        ID3D11VertexShader* _pVertexShader;
        ID3D11InputLayout* _pVertexLayout;
    };

}