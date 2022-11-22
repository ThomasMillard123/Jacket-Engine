#pragma once
#include<vector>

#include"Shader.h"
namespace Engine::Core::Graphics {
    class VertexShader : public Shader
    {
    public:
        VertexShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        ~VertexShader();
        HRESULT CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
        HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout);
        void CleanUp();
    private:
        ID3D11VertexShader* _pVertexShader;
        ID3D11InputLayout* _pVertexLayout;
    };

}