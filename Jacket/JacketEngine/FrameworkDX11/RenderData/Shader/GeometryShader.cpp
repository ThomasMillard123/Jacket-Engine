#include "GeometryShader.h"
namespace Engine::Core::Graphics {
    GeometryShader::GeometryShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
        CreateShader(szFileName, pd3dDevice);
    }
    GeometryShader::~GeometryShader()
    {
        CleanUp();
    }
    HRESULT GeometryShader::CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        HRESULT hr = CompileShaderFromFile(szFileName, "GS", "gs_5_0", &pVSBlob);
        if (FAILED(hr))
        {
            MessageBox(nullptr,
                L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return hr;
        }

        ID3D11GeometryShader* pGeoShader;
        // Create the vertex shader
        hr = pd3dDevice->CreateGeometryShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pGeoShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }
        _pGeometryShader = pGeoShader;



        return hr;
    }
    void GeometryShader::CleanUp()
    {
        if (_pGeometryShader) {
            _pGeometryShader->Release();
            _pGeometryShader = nullptr;
        }
    }
}