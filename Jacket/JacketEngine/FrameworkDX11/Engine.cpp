#include "Engine.h"

namespace Engine::Core {
	bool EngineClass::InitEngine(HINSTANCE hInstance, int nCmdShow, int width, int Hight, std::string WindowTitle, std::string WindowClass)
	{
		_HInstance = hInstance;
		_Window = new WindowCon::WindowContainer(hInstance, nCmdShow, width, Hight, WindowTitle, WindowClass);
		if (!_Window)
			return false;

		if (!Graphics::Graphics::Instance()->InitGraphics(_Window->GetHWnd())) {
			//clean up
			Graphics::Graphics::Instance()->CleanUp();
			return false;
		}
		/*if (FAILED(InitDevice()))
		{
			Cleanup();
			return 0;
		}*/

		return true;
	}

	EngineClass* EngineClass::Instance()
	{
		
		static EngineClass Engine;
		return &Engine;
	}


	bool EngineClass::ProcessMessages()
	{
		// Init message struct
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_NULL)
		{
			if (!IsWindow(_Window->GetHWnd()))
			{
				delete _Window;
				return false;
			}
		}

		return _Window;
		//return true;
	}

	void EngineClass::Update()
	{
	}

	void EngineClass::Draw()
	{

		//collect all objects
			//shadows
			//render world
			
		//post proccessing
		//imgui render

		//to screen
		
		
	}

	EngineClass::~EngineClass()
	{
		if (_Window) {
			delete _Window;
			_Window = nullptr;
		}
		Graphics::Graphics::Instance()->CleanUp();
	}

}