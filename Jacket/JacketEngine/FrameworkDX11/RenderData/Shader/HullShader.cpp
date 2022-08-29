#include "HullShader.h"
namespace Engine::Core::GraphicsCon {
    HRESULT HullShader::CreatHullShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        HRESULT hr = CompileShaderFromFile(szFileName, "HS", "hs_5_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        ID3D11HullShader* pHullShader;
        // Create the vertex shader
        hr = pd3dDevice->CreateHullShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pHullShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }
        _pHullShader = pHullShader;



        return hr;
    }
}
