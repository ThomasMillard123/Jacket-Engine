#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>

 namespace Engine::Core::GraphicsCon {

    class Shader
    {
    public:
        Shader();
        ~Shader();
        void CleanUp();
    protected:
        HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
        
    private:

    };

}