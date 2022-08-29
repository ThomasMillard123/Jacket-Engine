#pragma once
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>

namespace Engine::Core::GraphicsCon {
	class Graphics
	{
	public:
		bool InitGraphics(HWND _hWnd);
		static Graphics* Instance();
		void CleanUp();
	private:
		Graphics() {}
		~Graphics() {}

	private:

		D3D_DRIVER_TYPE         _driverType;
		D3D_FEATURE_LEVEL       _featureLevel;
		ID3D11Device* _pd3dDevice;
		ID3D11Device1* _pd3dDevice1;
		ID3D11DeviceContext* _pImmediateContext;
		ID3D11DeviceContext1* _pImmediateContext1;
		IDXGISwapChain* _pSwapChain;
		IDXGISwapChain1* _pSwapChain1;

		/*ID3D11RenderTargetView* _pRenderTargetView;
		ID3D11Texture2D* _pDepthStencil = nullptr;
		ID3D11DepthStencilView* _pDepthStencilView = nullptr;*/
		//ID3D11Buffer* _pConstantBuffer;





	};

}