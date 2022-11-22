#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>

 namespace Engine::Core::Graphics {

    class Shader
    {
    public:
        Shader() {}
        ~Shader() {}
        HRESULT CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice){}
        void CleanUp() {}
    protected:
        HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
    private:

    };

}