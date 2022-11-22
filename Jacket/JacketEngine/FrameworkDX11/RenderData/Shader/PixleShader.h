#pragma once
#include"Shader.h"
namespace Engine::Core::Graphics {
    class PixleShader: public Shader
    {
        public:
            PixleShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
            ~PixleShader();
            HRESULT CreateShader(const WCHAR* szFileName, ID3D11Device* pd3dDevice);
            void CleanUp();
        private:
            ID3D11PixelShader* _pPixelShader;
    };
}