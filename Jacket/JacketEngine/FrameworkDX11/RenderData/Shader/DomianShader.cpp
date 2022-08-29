#include "DomianShader.h"

namespace Engine::Core::GraphicsCon {
    HRESULT DomianShader::CreatDomianShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        HRESULT hr = CompileShaderFromFile(szFileName, "DS", "ds_5_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        ID3D11DomainShader* pDomainShader;
        // Create the vertex shader
        hr = pd3dDevice->CreateDomainShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pDomainShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }
        _pDomainShader = pDomainShader;



        return hr;
    }
}