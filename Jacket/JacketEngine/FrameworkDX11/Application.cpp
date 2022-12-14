#include "Application.h"

#include"M3dLoader.h"
Application* app;
LRESULT CALLBACK WindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;

        // Handle all other messages
    default:
    {
         //Get ptr to window class
        
        // Forward messages to window class
        return app->WndProc(hWnd, message, wParam, lParam);
    }



    }
}



//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;
    const auto& imio = ImGui::GetIO();
   
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;



    case WM_KEYUP:     
    case WM_KEYDOWN:  
    case WM_CHAR:
    {
        if (!imio.WantCaptureKeyboard) {
            return _controll->HandleInput(message, wParam, lParam);

        }
        return true;
    }
    break;
    //mouse input
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:  
    case WM_RBUTTONUP: 
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEHWHEEL:
    {
        if (!imio.WantCaptureMouse) {
            return _controll->HandleInput(message, wParam, lParam);

        }
    }
    case WM_INPUT:
    {
        if (!imio.WantCaptureMouse) {
            _controll->HandleInput(message, wParam, lParam);
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

    }
    break;
        // Note that this tutorial does not handle resizing (WM_SIZE) requests,
        // so we created the window without the resize border.

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

Application::Application() {
    _hInst = nullptr;
    _hWnd = nullptr;
    _driverType = D3D_DRIVER_TYPE_NULL;
    _featureLevel = D3D_FEATURE_LEVEL_11_0;
    _pd3dDevice = nullptr;
    _pd3dDevice1 = nullptr;
    _pImmediateContext = nullptr;
    _pImmediateContext1 = nullptr;
    _pSwapChain = nullptr;
    _pSwapChain1 = nullptr;
    _pRenderTargetView = nullptr;
    _pConstantBuffer = nullptr;

   

    _pConstantBuffer = nullptr;
    _pLightConstantBuffer = nullptr;



    DimGuiManager = new ImGuiManager();

    _controll = new InputControllor();
    _pLightContol = new LightControll();

    app = this;
}

Application::~Application()
{
    Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
    if (FAILED(InitWindow(hInstance, nCmdShow)))
        return 0;

    if (FAILED(InitDevice()))
    {
        Cleanup();
        return 0;
    }

    DimGuiManager->Initialize(_hWnd, _pd3dDevice, _pImmediateContext);

	return S_OK;
}

HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;


    _viewWidth = 1280;
    _viewHeight = 720;


    // Create window
    _hInst = hInstance;
    RECT rc = { 0, 0, _viewWidth, _viewHeight };

   

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!_hWnd)
        return E_FAIL;

    ShowWindow(_hWnd, nCmdShow);


    RAWINPUTDEVICE rid;
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02;
    rid.hwndTarget = NULL;
    rid.dwFlags = 0;

    if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == false) {
        return E_FAIL;
    }


    return S_OK;
}

HRESULT Application::InitMesh()
{
    HRESULT hr;
    //create shaders
    _Shader = new ShaderController();
    //TBN_VS= conversons to tangent space is done in vertex shader and without converts Parallax to world space
     hr = _Shader->NewShader("NoEffects", L"shaderNoNormalMap.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;
    
    hr= _Shader->NewShader("NormalMap", L"shader.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewShader("NormalMap_TBN_VS", L"shaderVertexTBN.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;


    hr = _Shader->NewShader("ParallaxMapping_TBN_VS", L"shaderParallaxMapping.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewShader("ParallaxMapping", L"shaderParallaxMapping1.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;


    hr = _Shader->NewShader("ParallaxOcMapping_TBN_VS", L"shaderParallaxOcMapping.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewShader("ParallaxOcMapping", L"shaderParallaxOcMapping1.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;


    hr = _Shader->NewShader("ParallaxOcShadingMapping_TBN_VS", L"shaderParallaxOcShadingMapping.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;
    hr = _Shader->NewShader("ParallaxOcShadingMapping", L"shaderParallaxOcShadingMapping1.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewShader("Depth(NotFullShader)", L"Depth.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewShader("DepthLight(NotFullShader)", L"DepthLight.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    //quadShader
    hr = _Shader->NewFullScreenShader("SolidColour", L"SolidColour.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewFullScreenShader("Gaussian1", L"Gaussian1.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewFullScreenShader("Fianl", L"Finalpass.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;
    hr = _Shader->NewFullScreenShader("Alpha", L"BloomAlphaTex.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;
    hr = _Shader->NewFullScreenShader("Gaussian2", L"Gaussian2.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewFullScreenShader("Fade", L"Fade.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _Shader->NewFullScreenShader("DepthOfField", L"DepthOfField.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;


    //gemoatry shader
    hr = _Shader->NewGeoShader("BillBord", L"BillBord.fx", _pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;


    //create object mesh
    hr = _GameObject.GetAppearance()->initMesh(_pd3dDevice, _pImmediateContext);
    if (FAILED(hr))
        return hr;

    hr = _GameObjectFloor.GetAppearance()->initMeshFloor(_pd3dDevice, _pImmediateContext, 10,10);
    if (FAILED(hr))
        return hr;


    _GameObjectFloor.GetTransfrom()->SetPosition(-5, -2, 5);

    //Terrain Genration
    _Terrain = new Terrain("Textures513\\coastMountain513.raw",XMFLOAT2(513,513),100,TerrainGenType::HightMapLoad ,_pd3dDevice, _pImmediateContext, _Shader);

    vector<string> texGround;
    texGround.push_back("Textures513/grass.dds");
    texGround.push_back("Textures513/darkdirt.dds");
    texGround.push_back("Textures513/lightdirt.dds");
    texGround.push_back("Textures513/stone.dds");
    texGround.push_back("Textures513/snow.dds");

    _Terrain->SetTex(texGround, _pd3dDevice);
    _Terrain->SetBlendMap("Textures513/blend.dds", _pd3dDevice);

    _VoxelTerrain = new TerrainVoxel(_pd3dDevice, _pImmediateContext, _Shader,3,3);


    AnimmationObject = new AnimatedModel("AnimationModel/soldier.m3d", _pd3dDevice, _pImmediateContext, _Shader);



    // Create the constant buffer
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(ConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);
    if (FAILED(hr))
        return hr;



    // Create the light constant buffer
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(LightPropertiesConstantBuffer);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pLightConstantBuffer);
    if (FAILED(hr))
        return hr;

    // Create the PostProcessing constant buffer
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(PostProcessingCB);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pPostProcessingConstantBuffer);
    if (FAILED(hr))
        return hr;



    BillBoradObject = new BillboardObject("Resources\\bricks_TEX.dds", 2, _pd3dDevice);

    

    return hr;
}
vector<float> CubicBezierBasis(float u) {
    float compla = 1 - u;	// complement of u
    // compute value of basis functions for given value of u
    float BF0 = compla * compla * compla;
    float BF1 = 3.0 * u * compla * compla;
    float BF2 = 3.0 * u * u * compla;
    float BF3 = u * u * u;
    
    vector<float> bfArray = { BF0, BF1, BF2, BF3 };

    return bfArray;

}
vector<XMFLOAT3> CubicBezierCurve(vector<XMFLOAT3> controlPoints) {
    vector<XMFLOAT3> Points;
    for (float i = 0.0f; i < 1.0f; i += 0.1f) {
        // Calculate value of each basis function for current u
        vector<float> basisFnValues = CubicBezierBasis(i);

        XMFLOAT3 sum = XMFLOAT3{0.0f,0.0f,0.0f};
        for (int cPointIndex = 0; cPointIndex <= 3; cPointIndex++) {
            // Calculate weighted sum (weightx * CPx)
            sum.x += controlPoints[cPointIndex].x * basisFnValues[cPointIndex];
            sum.y += controlPoints[cPointIndex].y * basisFnValues[cPointIndex];
            sum.z += controlPoints[cPointIndex].z * basisFnValues[cPointIndex];
        }

        DirectX::XMFLOAT3 point = sum;	// point for current u on cubic Bezier curve
        Points.push_back(point);
    }
    return Points;
}

HRESULT Application::InitWorld(int width, int height)
{
    // Initialize the camrea
    _pCamControll = new CameraController;
    _Camrea = new Camera(XMFLOAT3(0.0f, 0, -5), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), width, height, 0.01f, 100.0f);
    _Camrea->SetCamName("Light eye");
    _pCamControll->AddCam(_Camrea);
    _Camrea = new Camera(XMFLOAT3(0.0f, 0, -5), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), width, height, 0.01f, 100.0f);
    _Camrea->SetCamName("Free Cam");
    _pCamControll->AddCam(_Camrea);
    _Camrea = new Camera(XMFLOAT3(0.0f, 0, -5), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), width, height, 0.01f, 50.0f);
    _Camrea->SetCamName("Diss Cam");
    _pCamControll->AddCam(_Camrea);
    _controll->AddCam(_pCamControll);

    //postSettings
    postSettings.UseColour = false;
    postSettings.Color = XMFLOAT4{ 1.0f,1.0f,1.0f,0.0f };
    postSettings.UseBloom = false;
    postSettings.UseDepthOfF = false;
    postSettings.UseHDR = false;
    postSettings.UseBlur = false;
    postSettings.fadeAmount = 1.0f;
    postSettings.FarPlane = 100.0f;
    postSettings.focalDistance = 100.0f;
    postSettings.focalwidth = 100.0f;
    postSettings.blerAttenuation = 0.5f;



    SCREEN_VERTEX svQuad[4];

    svQuad[0].pos = XMFLOAT3(-1.0f, 1.0f, 0.0f);
    svQuad[0].tex = XMFLOAT2(0.0f, 0.0f);

    svQuad[1].pos = XMFLOAT3(1.0f, 1.0f, 0.0f);
    svQuad[1].tex = XMFLOAT2(1.0f, 0.0f);

    svQuad[2].pos = XMFLOAT3(-1.0f, -1.0f, 0.0f);
    svQuad[2].tex = XMFLOAT2(0.0f, 1.0f);

    svQuad[3].pos = XMFLOAT3(1.0f, -1.0f, 0.0f);
    svQuad[3].tex = XMFLOAT2(1.0f, 1.0f);


    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SCREEN_VERTEX) * 4;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = svQuad;
    HRESULT hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &g_pScreenQuadVB);
    if (FAILED(hr))
        return hr;
    vector<XMFLOAT3> a = { XMFLOAT3{0.0f,0.0f,0.0f},XMFLOAT3{2.0f,1.0f,0.0f},XMFLOAT3{5.0f,0.6f,0.0f},XMFLOAT3{6.0f,0.0f,0.0f} };
    DimGuiManager->points= CubicBezierCurve(a);
   


    

    return S_OK;
}

HRESULT Application::InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(_hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = _pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
    if (FAILED(hr))
        return hr;

    // Create swap chain
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = _pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&_pd3dDevice1));
        if (SUCCEEDED(hr))
        {
            (void)_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&_pImmediateContext1));
        }

        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;//  DXGI_FORMAT_R16G16B16A16_FLOAT;////DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(_pd3dDevice, _hWnd, &sd, nullptr, nullptr, &_pSwapChain1);
        if (SUCCEEDED(hr))
        {
            hr = _pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&_pSwapChain));
        }

        dxgiFactory2->Release();
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = _hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain);
    }

    // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
    dxgiFactory->MakeWindowAssociation(_hWnd, DXGI_MWA_NO_ALT_ENTER);

    dxgiFactory->Release();

    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
        return hr;

    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = _pd3dDevice->CreateTexture2D(&descDepth, nullptr, &_pDepthStencil);
    if (FAILED(hr))
        return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = _pd3dDevice->CreateDepthStencilView(_pDepthStencil, &descDSV, &_pDepthStencilView);
    if (FAILED(hr))
        return hr;



    //smaplers
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = _pd3dDevice->CreateSamplerState(&sampDesc, &m_pPointrLinear);
    if (FAILED(hr))
        return hr;

    sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    sampDesc.BorderColor[0] = 1.0f;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    hr = _pd3dDevice->CreateSamplerState(&sampDesc, &m_pLINEARBORDER);
    if (FAILED(hr))
        return hr;

    // Create a render target view 2nd
    RenderTargetControl = new RenderTargetControll();
    RenderTargetControl->CreatRenderTarget("RTT",width, height,_pd3dDevice);
    RenderTargetControl->CreatRenderTarget("Depth", width, height, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("DepthOfField", width, height, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("Fade", width, height, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("Gauss1", width / 2, height / 2, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("Gauss2", width / 2, height / 2, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("DownSample", width / 2, height / 2, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("UpSample", width, height, _pd3dDevice);
    RenderTargetControl->CreatRenderTarget("alpha", width, height, _pd3dDevice);

 

    DepthLight= new ShadowMap(_pd3dDevice, width, height);
  
    RSControll = new RasterStateManager();

    D3D11_RASTERIZER_DESC cmdesc;
    ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
    cmdesc.FillMode = D3D11_FILL_SOLID;
    cmdesc.CullMode = D3D11_CULL_BACK;
    RSControll->CreatRasterizerState(_pd3dDevice, cmdesc, "RSCullBack");
  
    ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
    cmdesc.FillMode = D3D11_FILL_WIREFRAME;
    cmdesc.CullMode = D3D11_CULL_BACK;
    RSControll->CreatRasterizerState(_pd3dDevice, cmdesc, "RWireframe");



    ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
    cmdesc.FillMode = D3D11_FILL_SOLID;
    cmdesc.CullMode = D3D11_CULL_NONE;
    RSControll->CreatRasterizerState(_pd3dDevice, cmdesc, "RSCullNone");

    hr = InitMesh();
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Failed to initialise mesh.", L"Error", MB_OK);
        return hr;
    }

    hr = InitWorld(width, height);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"Failed to initialise world.", L"Error", MB_OK);
        return hr;
    }

   

    //creat Lights
    _pLightContol->AddLight("MainPoint", true, LightType::PointLight, XMFLOAT4(0.0f, 0.0f, -4.0f,0.0f), XMFLOAT4(Colors::White), XMConvertToRadians(45.0f), 1.0f, 0.0f, 0.0f, _pd3dDevice, _pImmediateContext);
    _pLightContol->AddLight("Point", true, LightType::SpotLight, XMFLOAT4(0.0f, 5.0f, 0.0f, 0.0f), XMFLOAT4(Colors::White), XMConvertToRadians(10.0f), 1.0f, 0.0f, 0.0f, _pd3dDevice, _pImmediateContext);

    return S_OK;
}
void Application::Update()
{ 
    float t = calculateDeltaTime(); // capped at 60 fps
    if (t == 0.0f)
        return;
    
    _controll->Update();
    _pCamControll->Update(); 
    _Terrain->Update();
    // Update the cube transform, material etc. 
    _GameObject.update(t, _pImmediateContext);
    _GameObjectFloor.update(t, _pImmediateContext);
    _pLightContol->update(t, _pImmediateContext);
    BillBoradObject->UpdatePositions(_pImmediateContext);

    AnimmationObject->Update(t);
}

void Application::Draw()
{
  
    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)_viewWidth;
    vp.Height = (FLOAT)	_viewHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    _pImmediateContext->RSSetViewports(1, &vp);
    RenderTargetControl->GetRenderTarget("RTT")->SetRenderTarget(_pImmediateContext);


   
    // Present our back buffer to our front buffer
    _pSwapChain->Present(1, 0);
}



float Application::calculateDeltaTime()
{
     //Update our time
    static float deltaTime = 0.0f;
    static ULONGLONG timeStart = 0;
    ULONGLONG timeCur = GetTickCount64();
    if (timeStart == 0)
        timeStart = timeCur;
    deltaTime = (timeCur - timeStart) / 1000.0f;
    timeStart = timeCur;

    float FPS60 = 1.0f / 60.0f;
    static float cummulativeTime = 0;

    // cap the framerate at 60 fps 
    cummulativeTime += deltaTime;
    if (cummulativeTime >= FPS60) {
        cummulativeTime = cummulativeTime - FPS60;
    }
    else {
        return 0;
    }

    return deltaTime;
}

void Application::setupLightForRender()
{
        
        LightPropertiesConstantBuffer lightProperties;
        lightProperties.EyePosition = _pCamControll->GetCam(0)->GetPositionFloat4();
        lightProperties.Lights[0] = _pLightContol->GetLight(0)->GetLightData();
        lightProperties.Lights[1] = _pLightContol->GetLight(1)->GetLightData();
        _pImmediateContext->UpdateSubresource(_pLightConstantBuffer, 0, nullptr, &lightProperties, 0, 0);
}


void Application::Cleanup()
{
        _GameObject.cleanup();
        _GameObjectFloor.cleanup();

        delete _controll;
        _controll = nullptr;
        
        delete _pCamControll;
        _pConstantBuffer = nullptr;

        delete _pLightContol;
        _pLightContol = nullptr;

        delete DimGuiManager;
        DimGuiManager = nullptr;

        delete _Shader;
        _Shader = nullptr;

        delete RenderTargetControl;
        RenderTargetControl = nullptr;

        delete BillBoradObject;
        BillBoradObject = nullptr;
        delete DepthLight;
        DepthLight = nullptr;


        delete _Terrain;
        _Terrain = nullptr;


        delete _VoxelTerrain;
        _VoxelTerrain = nullptr;


        delete AnimmationObject;
        AnimmationObject = nullptr;

        // Remove any bound render target or depth/stencil buffer
        ID3D11RenderTargetView* nullViews[] = { nullptr };
        _pImmediateContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    
        if( _pImmediateContext ) _pImmediateContext->ClearState();
        // Flush the immediate context to force cleanup
        if (_pImmediateContext1) _pImmediateContext1->Flush();
        _pImmediateContext->Flush();
    
        if (_pLightConstantBuffer)
            _pLightConstantBuffer->Release();
      
        if( _pConstantBuffer ) _pConstantBuffer->Release();
        if (_pPostProcessingConstantBuffer)_pPostProcessingConstantBuffer->Release();

        if( _pDepthStencil ) _pDepthStencil->Release();
        if( _pDepthStencilView ) _pDepthStencilView->Release();
        if( _pRenderTargetView ) _pRenderTargetView->Release();
        if( _pSwapChain1 ) _pSwapChain1->Release();
        if( _pSwapChain ) _pSwapChain->Release();
        if( _pImmediateContext1 ) _pImmediateContext1->Release();
        if( _pImmediateContext ) _pImmediateContext->Release();
    
    
        if (g_pScreenQuadVB) g_pScreenQuadVB->Release();
        if (m_pPointrLinear) m_pPointrLinear->Release();
        if (m_pPointrLinear) m_pLINEARBORDER->Release();
       

        ID3D11Debug* debugDevice = nullptr;
        _pd3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDevice));
    
        if (_pd3dDevice1) _pd3dDevice1->Release();
        if (_pd3dDevice) _pd3dDevice->Release();
    
        // handy for finding dx memory leaks
        debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    
        if (debugDevice)
            debugDevice->Release();

}

bool Application::InputControll(MSG msg)
{
    
    return false;
}


