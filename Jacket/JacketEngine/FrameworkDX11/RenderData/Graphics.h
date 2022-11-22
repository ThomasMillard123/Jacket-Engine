#pragma once
#include <windowsx.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <DirectXCollision.h>


#include"RasterStateManager.h"
#include"RenderTargetControll.h"
#include"ShaderController.h"
namespace Engine::Core::Graphics {
	/// <summary>
	/// DirectX Data
	/// </summary>
	class Graphics
	{
	public:
		bool InitGraphics(HWND _hWnd);
		static Graphics* Instance();
		void CleanUp();


		IDXGISwapChain* GetSwapChaine() { return _pSwapChain; }
		ID3D11DeviceContext* GetDeviceContext() { return _pImmediateContext; }
		ID3D11Device* GetDevice() { return _pd3dDevice; }

		bool UpdateWidthAndHight();
	private:
		Graphics() {
		
			_driverType = D3D_DRIVER_TYPE_NULL;
			_featureLevel = D3D_FEATURE_LEVEL_11_0;
			_pd3dDevice = nullptr;
			_pd3dDevice1 = nullptr;
			_pImmediateContext = nullptr;
			_pImmediateContext1 = nullptr;
			_pSwapChain = nullptr;
			_pSwapChain1 = nullptr;
		
		}
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

		/*RenderTargetControll* _pRTControll;
		RasterStateManager* _pRSControll;
		ShaderResource* _pShaderControll;*/

	};

}