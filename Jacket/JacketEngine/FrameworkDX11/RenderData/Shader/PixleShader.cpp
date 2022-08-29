#include "PixleShader.h"
namespace Engine::Core::GraphicsCon {
    HRESULT PixleShader::CreatPixleShader(WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        HRESULT hr = CompileShaderFromFile(szFileName, "PS", "ps_5_0", &pPSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        // Create the pixel shader
        hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return hr;


        return hr;
    }
}