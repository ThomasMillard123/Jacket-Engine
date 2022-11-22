#include "VertexShader.h"

#include<string>
#include"..\Buffers\DynamicConstantBuffer.h"
#include"..\..\Utilitys\StringHelper.h"

namespace Engine::Core::Graphics {
    VertexShader::VertexShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
        CreateShader(szFileName, pd3dDevice);
    }
    VertexShader::~VertexShader()
    {
        CleanUp();
    }
    HRESULT VertexShader::CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice)
    {
       
        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        HRESULT hr = CompileShaderFromFile(szFileName, "VS", "vs_5_0", &pVSBlob);
       

        if (FAILED(hr))
        {

            LPCWSTR error = L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file. ";
            std::wstring df = std::wstring(error) + szFileName;
            error = df.c_str();
            MessageBox(nullptr,
                error, L"Error", MB_OK);
            return hr;
        }
        // Create the vertex shader
        hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }

        //layout creation
        hr = CreateInputLayoutDescFromVertexShaderSignature(pVSBlob, pd3dDevice, &_pVertexLayout);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return hr;
        }


        return hr;
    }
    HRESULT VertexShader::CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout)
    {
        // Reflect shader info
        ID3D11ShaderReflection* pVertexShaderReflection = NULL;
        if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
        {
            return S_FALSE;
        }

        // Get shader info
        D3D11_SHADER_DESC shaderDesc;
        pVertexShaderReflection->GetDesc(&shaderDesc);
       
        // Read input layout description from shader info
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
        for (UINT32 i = 0; i < shaderDesc.InputParameters; i++)
        {
            D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
            pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

            // fill out input element desc
            D3D11_INPUT_ELEMENT_DESC elementDesc;
            elementDesc.SemanticName = paramDesc.SemanticName;
            elementDesc.SemanticIndex = paramDesc.SemanticIndex;
            elementDesc.InputSlot = 0;
            elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            elementDesc.InstanceDataStepRate = 0;

            // determine DXGI format
            if (paramDesc.Mask == 1)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
            }
            else if (paramDesc.Mask <= 3)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
            }
            else if (paramDesc.Mask <= 7)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            }
            else if (paramDesc.Mask <= 15)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            }

            //save element desc
            inputLayoutDesc.push_back(elementDesc);
        }

        // Try to create Input Layout
        HRESULT hr = pD3DDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout);



        //vertex build 


        //constanct buffer reflection 

       
        
        for (size_t i = 0; i < shaderDesc.ConstantBuffers; i++)
        {

            Buffers::RawLayout CBlayout;

            ID3D11ShaderReflectionConstantBuffer* cb = pVertexShaderReflection->GetConstantBufferByIndex(i);
            if (cb)
            {
                D3D11_SHADER_BUFFER_DESC cbDesc;
                cb->GetDesc(&cbDesc);
               
                if (cbDesc.Type == D3D11_CT_CBUFFER)
                {
                    for (unsigned i = 0; i < cbDesc.Variables; ++i)
                    {
                        ID3D11ShaderReflectionVariable* var = cb->GetVariableByIndex(i);

                        D3D11_SHADER_VARIABLE_DESC varDesc;
                        var->GetDesc(&varDesc);

                        ID3D11ShaderReflectionType* type = var->GetType();
                        D3D11_SHADER_TYPE_DESC typeDesc;
                        type->GetDesc(&typeDesc);

                        if ("float4x4" == Utilitys::StringFunc::LPCSTRToString(typeDesc.Name)) {
                            CBlayout.Add<Buffers::Matrix>(Utilitys::StringFunc::LPCSTRToString(varDesc.Name));
                        }
                        if ("float4" == Utilitys::StringFunc::LPCSTRToString(typeDesc.Name)) {
                            CBlayout.Add<Buffers::Float4>(Utilitys::StringFunc::LPCSTRToString(varDesc.Name));
                        }
                        for (unsigned j = 0; j < typeDesc.Members; ++j)
                        {
                            ID3D11ShaderReflectionType* memberType = type->GetMemberTypeByIndex(j);
                            

                            D3D11_SHADER_TYPE_DESC memberTypeDesc;
                            memberType->GetDesc(&memberTypeDesc);


                        }
                    }
                }
            }

            
            Buffers::Buffer buff = Buffers::Buffer(std::move(CBlayout));
            buff.CreatBuffer(pD3DDevice);
            
        }

        //Free allocation shader reflection memory
        pVertexShaderReflection->Release();
        return hr;
    }

    void VertexShader::CleanUp()
    {
        if (_pVertexShader) {
            _pVertexShader->Release();
            _pVertexShader = nullptr;
        }

        if (_pVertexLayout) {
            _pVertexLayout->Release();
            _pVertexLayout = nullptr;
        }
    }

}