//
// DeviceResources.cpp - A wrapper for the Direct3D 11 device and swapchain
//                       (requires DirectX 11.3 Runtime)
//


#include "EngineMinimal.h"
#include "EngineHelper.h"
#include "DeviceResources.h"

using namespace D2D1;
using namespace DirectX;
using namespace DX;
using namespace std;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

namespace DisplayMetrics
{
    // 고해상도 디스플레이는 렌더링하는 데 많은 GPU 및 배터리 전원이 필요할 수 있습니다.
    // 예를 들어 고해상도 휴대폰의 게임에서 고화질로 초당 60프레임을 렌더링하려는
    // 경우 짧은 배터리 수명으로 인해 문제가 발생할 수 있습니다.
    // 모든 플랫폼 및 폼 팩터에서 고화질로 렌더링하는 결정은
    // 신중하게 내려야 합니다.
    static const bool SupportHighResolutions = false;

    // “고해상도” 디스플레이를 정의하는 기본 임계값입니다. 임계값을 초과하거나
    // SupportHighResolutions가 false인 경우 크기가 50%로
    //줄어듭니다.
    static const float DpiThreshold = 192.0f;		// 표준 데스크톱 디스플레이의 200%입니다.
    static const float WidthThreshold = 1920.0f;	// 너비가 1080p입니다.
    static const float HeightThreshold = 1080.0f;	// 높이가 1080p입니다.
};

// Constants used to calculate screen rotations
namespace ScreenRotation
{
    // 0-degree Z-rotation
    static const XMFLOAT4X4 Rotation0(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 90-degree Z-rotation
    static const XMFLOAT4X4 Rotation90(
        0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 180-degree Z-rotation
    static const XMFLOAT4X4 Rotation180(
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 270-degree Z-rotation
    static const XMFLOAT4X4 Rotation270(
        0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

// Constructor for DeviceResources.
DX::DeviceResources::DeviceResources(
    DXGI_FORMAT backBufferFormat,
    DXGI_FORMAT depthBufferFormat,
    UINT backBufferCount,
    D3D_FEATURE_LEVEL minFeatureLevel,
    unsigned int flags) noexcept :
    m_screenViewport{},
    m_backBufferFormat(backBufferFormat),
    m_depthBufferFormat(depthBufferFormat),
    m_backBufferCount(backBufferCount),
    m_d3dMinFeatureLevel(minFeatureLevel),
    m_window(nullptr),    
    m_d3dFeatureLevel(D3D_FEATURE_LEVEL_9_1),
    m_rotation(DXGI_MODE_ROTATION_IDENTITY),
    m_dxgiFactoryFlags(0),
    m_outputSize(),
    m_logicalSize(),
    m_RasterizationScale(-1.0),
    m_effectiveRasterizationScale(-1.0f),
    m_orientationTransform3D(ScreenRotation::Rotation0),
    m_colorSpace(DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709),    
    m_options(flags),
    m_deviceNotify(nullptr)
{        
    CreateDeviceIndependentResources();
    CreateDeviceResources();
}

#pragma region CreateResources
void DX::DeviceResources::CreateDeviceIndependentResources()
{        
    // Direct2D 리소스를 초기화합니다.
    D2D1_FACTORY_OPTIONS options;
    ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
    // 프로젝트가 디버그 빌드 중인 경우 SDK 레이어를 통해 Direct2D 디버깅을 사용합니다.
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

    // DirectWrite 팩터리를 초기화합니다.
    DX::ThrowIfFailed(
        DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory3),
            (::IUnknown**)&m_dwriteFactory
        )
    );

    // Direct2D 팩터리를 초기화합니다.
    DX::ThrowIfFailed(
        D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            __uuidof(ID2D1Factory3),
            &options,
            (void**)m_d2dFactory.ReleaseAndGetAddressOf()
        )
    );

    //WIC(Windows Imaging Component) 팩터리를 초기화합니다.
    
    DX::ThrowIfFailed(
        CoCreateInstance(
            CLSID_WICImagingFactory2,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(m_wicFactory.addressof())
        )
    );
}

// Configures the Direct3D device, and stores handles to it and the device context.
void DeviceResources::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    if (SdkLayersAvailable())
    {
        // If the project is in a debug build, enable debugging via SDK Layers with this flag.
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    } 
    else
    {
        OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
    }
#endif

#ifdef _DEBUG
    {
        wil::com_ptr<IDXGIInfoQueue> dxgiInfoQueue;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.addressof()))))
        {
            m_dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);

            DXGI_INFO_QUEUE_MESSAGE_ID hide[] =
            {
                80 /* IDXGISwapChain::GetContainingOutput: The swapchain's adapter does not control the output on which the swapchain's window resides. */,
            };
            DXGI_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = static_cast<UINT>(std::size(hide));
            filter.DenyList.pIDList = hide;
            dxgiInfoQueue->AddStorageFilterEntries(DXGI_DEBUG_DXGI, &filter);
        }
    }
#endif

    ThrowIfFailed(CreateDXGIFactory2(m_dxgiFactoryFlags, IID_PPV_ARGS(m_dxgiFactory.put())));

    // Determines whether tearing support is available for fullscreen borderless windows.
    if (m_options & c_AllowTearing)
    {
        BOOL allowTearing = FALSE;

        wil::com_ptr<IDXGIFactory5> factory5;
        m_dxgiFactory.query_to(factory5.addressof());
        
        //HRESULT hr = m_dxgiFactory.as(&factory5);
        if (!factory5)
        {
            hr = factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
        }

        if (FAILED(hr) || !allowTearing)
        {
            m_options &= ~c_AllowTearing;
#ifdef _DEBUG
            OutputDebugStringA("WARNING: Variable refresh rate displays not supported");
#endif
        }
    }

    // Determine DirectX hardware feature levels this app will support.
    static const D3D_FEATURE_LEVEL s_featureLevels[] =
    {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    UINT featLevelCount = 0;
    for (; featLevelCount < static_cast<UINT>(std::size(s_featureLevels)); ++featLevelCount)
    {
        if (s_featureLevels[featLevelCount] < m_d3dMinFeatureLevel)
            break;
    }

    if (!featLevelCount)
    {
        throw std::out_of_range("minFeatureLevel too high");
    }

    wil::com_ptr_nothrow<IDXGIAdapter1> adapter;    
    GetHardwareAdapter( &adapter );

    // Create the Direct3D 11 API device object and a corresponding context.
    wil::com_ptr_nothrow<ID3D11Device> device;
    wil::com_ptr_nothrow<ID3D11DeviceContext> context;

    hr = E_FAIL;
    if (adapter)
    {
        hr = D3D11CreateDevice(
            adapter.get(),
            D3D_DRIVER_TYPE_UNKNOWN,
            nullptr,
            creationFlags,              // Set debug and Direct2D compatibility flags.
            s_featureLevels,
            featLevelCount,
            D3D11_SDK_VERSION,
            &device,                    // Returns the Direct3D device created.
            &m_d3dFeatureLevel,         // Returns feature level of device created.
            &context                     // Returns the device immediate context.
        );
    }
#if defined(NDEBUG)
    else
    {
        throw std::runtime_error("No Direct3D hardware device found");
    }
#else
    if (FAILED(hr))
    {
        /*
           If the initialization fails, fall back to the WARP device.
           For more information on WARP, see:
           http://go.microsoft.com/fwlink/?LinkId=286690
        */
        hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
            nullptr,
            creationFlags,
            s_featureLevels,
            featLevelCount,
            D3D11_SDK_VERSION,
            device.addressof(),
            &m_d3dFeatureLevel,
            context.addressof()
        );

        if (SUCCEEDED(hr))
        {
            OutputDebugStringA("Direct3D Adapter - WARP\n");
        }
    }
#endif

    ThrowIfFailed(hr);

#ifndef NDEBUG
    wil::com_ptr_nothrow<ID3D11Debug> d3dDebug;    
    if (SUCCEEDED(device.query_to(d3dDebug.addressof())))
    {
        wil::com_ptr_nothrow<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.query_to(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide[] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = static_cast<UINT>(std::size(hide));
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif
    
    ThrowIfFailed(device.query_to(&m_d3dDevice));
    ThrowIfFailed(context.query_to(&m_d3dContext));

    // Direct2D 디바이스 개체 및 해당 컨텍스트를 만듭니다.
    com_ptr_nothrow<IDXGIDevice3> dxgiDevice;
    DX::ThrowIfFailed(
        m_d3dDevice.query_to(dxgiDevice.addressof())
    );

    DX::ThrowIfFailed(
        m_d2dFactory->CreateDevice(dxgiDevice.get(), &m_d2dDevice)
    );

    DX::ThrowIfFailed(
        m_d2dDevice->CreateDeviceContext(
            D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
            &m_d2dContext
        )
    );

    m_d2dContext->GetDpi(&m_dpi, &m_dpi);
}

// These resources need to be recreated every time the window size is changed.
void DeviceResources::CreateWindowSizeDependentResources()
{
    //if (!m_window)
    //{
    //    throw std::logic_error("Call SetWindow with a valid CoreWindow pointer");
    //}

    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews[] = { nullptr };
    m_d3dContext->OMSetRenderTargets(static_cast<UINT>(std::size(nullViews)), nullViews, nullptr);    
    m_d3dRenderTargetView = nullptr;
    m_d3dDepthStencilView = nullptr;
    m_renderTarget = nullptr;
    m_depthStencil = nullptr;
    m_d3dContext->Flush();
    m_d2dContext->SetTarget(nullptr);
    m_d2dTargetBitmap = nullptr;

    UpdateRenderTargetSize();


    // 스왑 체인의 너비와 높이는 창의 가로 방향 너비 및 높이를
    // 기준으로 해야 합니다. 창이 기준 방향이 아닌 경우에는
    // 치수를 반대로 해야 합니다.
    //DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();
    // Determine the render target size in pixels.        
    //bool swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
    //m_d3dRenderTargetSize.Width = swapDimensions ? m_outputSize.Height : m_outputSize.Width;
    //m_d3dRenderTargetSize.Height = swapDimensions ? m_outputSize.Width : m_outputSize.Height;
    m_d3dRenderTargetSize.Width = m_outputSize.Width;
    m_d3dRenderTargetSize.Height = m_outputSize.Height;
        ;

    const DXGI_FORMAT backBufferFormat = NoSRGB(m_backBufferFormat);
    const UINT backBufferWidth = std::max<UINT>(static_cast<UINT>(m_d3dRenderTargetSize.Width), 1u);
    const UINT backBufferHeight = std::max<UINT>(static_cast<UINT>(m_d3dRenderTargetSize.Height), 1u);

    if (m_swapChain)
    {
        // If the swap chain already exists, resize it.
        HRESULT hr = m_swapChain->ResizeBuffers(
            m_backBufferCount,
            lround(m_d3dRenderTargetSize.Width),
            lround(m_d3dRenderTargetSize.Height),
            backBufferFormat,
            (m_options & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u
        );

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
#ifdef _DEBUG
            char buff[64] = {};
            sprintf_s(buff, "Device Lost on ResizeBuffers: Reason code 0x%08X\n",
                static_cast<unsigned int>((hr == DXGI_ERROR_DEVICE_REMOVED) ? m_d3dDevice->GetDeviceRemovedReason() : hr));
            OutputDebugStringA(buff);
#endif
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            HandleDeviceLost();

            // Everything is set up now. Do not continue execution of this method. HandleDeviceLost will reenter this method
            // and correctly set up the new device.
            return;
        }
        else
        {
            ThrowIfFailed(hr);
        }
    }
    else
    {
        // Create a descriptor for the swap chain.
        DXGI_SCALING scaling;
        if(m_options & c_UseXAML)
            scaling = DisplayMetrics::SupportHighResolutions ? DXGI_SCALING_NONE : DXGI_SCALING_STRETCH;
        else
            scaling = DisplayMetrics::SupportHighResolutions ? DXGI_SCALING_NONE : DXGI_SCALING_ASPECT_RATIO_STRETCH;
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
        swapChainDesc.Width = backBufferWidth;
        swapChainDesc.Height = backBufferHeight;
        swapChainDesc.Format = backBufferFormat;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = m_backBufferCount;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Scaling = scaling;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;       //DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// 모든 Microsoft Store 앱은 _FLIP_ SwapEffects를 사용해야 합니다.
        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        swapChainDesc.Flags = (m_options & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u;

        // XAML interop을 사용하는 경우 스왑 체인은 컴퍼지션용으로 만들어야 합니다.
        
        com_ptr_nothrow<IDXGISwapChain1> swapChain;
        if (m_options & c_UseXAML)
        {
            // XAML interop을 사용하는 경우 스왑 체인은 컴퍼지션용으로 만들어야 합니다.            
            DX::ThrowIfFailed(
                m_dxgiFactory->CreateSwapChainForComposition(
                    m_d3dDevice.get(),
                    &swapChainDesc,
                    nullptr,
                    swapChain.addressof()
                )
            );
        }
        else
        {
            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
            fsSwapChainDesc.Windowed = TRUE;
            // Create a swap chain for the window.        
            //ThrowIfFailed(m_dxgiFactory->CreateSwapChainForCoreWindow(
            //    m_d3dDevice.Get(),
            //    m_window,
            //    &swapChainDesc,
            //    nullptr,
            //    swapChain.GetAddressOf()
                ThrowIfFailed(m_dxgiFactory->CreateSwapChainForHwnd(
                m_d3dDevice.get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                swapChain.addressof()
            ));   
        }

        ThrowIfFailed(swapChain.query_to(&m_swapChain));

        //auto panelNative = m_swapchainPanel.as<ISwapChainPanelNative>();
        //panelNative->SetSwapChain(m_swapChain.Get());
        

        if (m_options & c_UseXAML)
        {
            // 스왑 체인을 SwapChainPanel과 연결
            // UI 변경 내용은 UI 스레드에 다시 디스패치해야 함            
            //GetSwapchainPanel().Dispatcher().RunAsync(CoreDispatcherPriority::High, DispatchedHandler([=]()            
            GetSwapchainPanel().DispatcherQueue().TryEnqueue(winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [this]
                {
                    // SwapChainPanel에 대한 기본 인터페이스 가져오기                                                            
                    //auto panelNative = GetSwapchainPanel().as<ISwapChainPanelNative>();
                    auto panelNative = GetSwapchainPanel().as<ISwapChainPanelNative>();
                    DX::ThrowIfFailed(panelNative->SetSwapChain(m_swapChain.get()));
                });

            // Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
            // ensures that the application will only render after each VSync, minimizing power consumption.
            com_ptr_nothrow<IDXGIDevice3> dxgiDevice;
            ThrowIfFailed(m_d3dDevice.query_to(&dxgiDevice));
            ThrowIfFailed(dxgiDevice->SetMaximumFrameLatency(1));
        }

      
    }

    // Handle color space settings for HDR
    UpdateColorSpace();

    // Set the proper orientation for the swap chain, and generate
    // matrix transformations for rendering to the rotated swap chain.
    //switch (displayRotation)
    //{
    //default:
    //case DXGI_MODE_ROTATION_IDENTITY:
    //    m_orientationTransform2D = Matrix3x2F::Identity();
    //    m_orientationTransform3D = ScreenRotation::Rotation0;
    //    break;

    //case DXGI_MODE_ROTATION_ROTATE90:
    //    m_orientationTransform2D =
    //        Matrix3x2F::Rotation(90.0f) *
    //        Matrix3x2F::Translation(m_logicalSize.Height, 0.0f);
    //    m_orientationTransform3D = ScreenRotation::Rotation270;
    //    break;

    //case DXGI_MODE_ROTATION_ROTATE180:
    //    m_orientationTransform2D =
    //        Matrix3x2F::Rotation(180.0f) *
    //        Matrix3x2F::Translation(m_logicalSize.Width, m_logicalSize.Height);
    //    m_orientationTransform3D = ScreenRotation::Rotation180;
    //    break;

    //case DXGI_MODE_ROTATION_ROTATE270:
    //    m_orientationTransform2D =
    //        Matrix3x2F::Rotation(270.0f) *
    //        Matrix3x2F::Translation(0.0f, m_logicalSize.Width);
    //    m_orientationTransform3D = ScreenRotation::Rotation90;
    //    break;
    //}

    ThrowIfFailed(m_swapChain->SetRotation(m_rotation));

    // 스왑 체인에서 역비율 설정 ??
    if (m_options & c_UseXAML)
    {
        DXGI_MATRIX_3X2_F inverseScale = { 0 };
        inverseScale._11 = 1.0f / m_effectiveCompositionScaleX;
        inverseScale._22 = 1.0f / m_effectiveCompositionScaleY;
        com_ptr_nothrow<IDXGISwapChain2> spSwapChain2;
        DX::ThrowIfFailed(
            m_swapChain.query_to(spSwapChain2.addressof())
        );

        DX::ThrowIfFailed(
            spSwapChain2->SetMatrixTransform(&inverseScale)
        );
    }

    // Create a render target view of the swap chain back buffer.
    ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(m_renderTarget.put())));

    CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(D3D11_RTV_DIMENSION_TEXTURE2D, m_backBufferFormat);
    ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(
        m_renderTarget.get(),
        &renderTargetViewDesc,
        m_d3dRenderTargetView.put()
    ));

    if (m_depthBufferFormat != DXGI_FORMAT_UNKNOWN)
    {
        // Create a depth stencil view for use with 3D rendering if needed.
        CD3D11_TEXTURE2D_DESC depthStencilDesc(
            m_depthBufferFormat,
            backBufferWidth,
            backBufferHeight,
            1, // This depth stencil view has only one texture.
            1, // Use a single mipmap level.
            D3D11_BIND_DEPTH_STENCIL
        );

        ThrowIfFailed(m_d3dDevice->CreateTexture2D(
            &depthStencilDesc,
            nullptr,
            m_depthStencil.put()
        ));

        CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
        ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(
            m_depthStencil.get(),
            &depthStencilViewDesc,
            m_d3dDepthStencilView.addressof()
        ));
    }

    // Set the 3D rendering viewport to target the entire window.
    m_screenViewport = CD3D11_VIEWPORT(
        0.0f,
        0.0f,
        static_cast<float>(backBufferWidth),
        static_cast<float>(backBufferHeight)
    );

    // 스왑 체인 백 버퍼에 연결된 Direct2D 대상
    // 비트맵을 만들고 이를 현재 대상으로 설정합니다.
    D2D1_BITMAP_PROPERTIES1 bitmapProperties =
        D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
            (float)m_RasterizationScale,
            (float)m_RasterizationScale
        );

    com_ptr_nothrow<IDXGISurface2> dxgiBackBuffer;
    DX::ThrowIfFailed(
        m_swapChain->GetBuffer(0, IID_PPV_ARGS(dxgiBackBuffer.addressof()))
    );

    DX::ThrowIfFailed(
        m_d2dContext->CreateBitmapFromDxgiSurface(
            dxgiBackBuffer.get(),            
            &bitmapProperties,
            m_d2dTargetBitmap.put()
        )
    );

    m_d2dContext->SetTarget(m_d2dTargetBitmap.get());
    m_d2dContext->SetDpi(m_dpi * m_effectiveRasterizationScale, m_dpi * m_effectiveRasterizationScale);

    // 모든 Microsoft Store 앱에 회색조 텍스트 앤티앨리어싱을 사용하는 것이 좋습니다.
    m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
}

// This method acquires the first available hardware adapter.
// If no such adapter can be found, *ppAdapter will be set to nullptr.
void DeviceResources::GetHardwareAdapter(IDXGIAdapter1** ppAdapter)
{
    *ppAdapter = nullptr;

    com_ptr_nothrow<IDXGIAdapter1> adapter;

    com_ptr_nothrow<IDXGIFactory6> factory6;
    HRESULT hr = m_dxgiFactory.query_to(factory6.addressof());
    if (SUCCEEDED(hr))
    {
        for (UINT adapterIndex = 0;
            SUCCEEDED(factory6->EnumAdapterByGpuPreference(
                adapterIndex,
                DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
                IID_PPV_ARGS(adapter.put())));
            adapterIndex++)
        {
            DXGI_ADAPTER_DESC1 desc;
            ThrowIfFailed(adapter->GetDesc1(&desc));

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                continue;
            }

#ifdef _DEBUG
            wchar_t buff[256] = {};
            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
            OutputDebugStringW(buff);
#endif

            break;
        }
    }

    if (!adapter)
    {
        for (UINT adapterIndex = 0;
            SUCCEEDED(m_dxgiFactory->EnumAdapters1(
                adapterIndex,
                adapter.put()));
            adapterIndex++)
        {
            DXGI_ADAPTER_DESC1 desc;
            ThrowIfFailed(adapter->GetDesc1(&desc));

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                continue;
            }

#ifdef _DEBUG
            wchar_t buff[256] = {};
            swprintf_s(buff, L"Direct3D Adapter (%u): VID:%04X, PID:%04X - %ls\n", adapterIndex, desc.VendorId, desc.DeviceId, desc.Description);
            OutputDebugStringW(buff);
#endif

            break;
        }
    }

    *ppAdapter = adapter.detach();
}

// Sets the color space for the swap chain in order to handle HDR output.
void DeviceResources::UpdateColorSpace()
{
    DXGI_COLOR_SPACE_TYPE colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709;

    bool isDisplayHDR10 = false;

    if (m_swapChain)
    {
        com_ptr_nothrow<IDXGIOutput> output;
        if (SUCCEEDED(m_swapChain->GetContainingOutput(output.addressof())))
        {
            com_ptr_nothrow<IDXGIOutput6> output6;
            if (SUCCEEDED(output.query_to(output6.addressof())))
            {
                DXGI_OUTPUT_DESC1 desc;
                ThrowIfFailed(output6->GetDesc1(&desc));

                if (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020)
                {
                    // Display output is HDR10.
                    isDisplayHDR10 = true;
                }
            }
        }
    }

    if ((m_options & c_EnableHDR) && isDisplayHDR10)
    {
        switch (m_backBufferFormat)
        {
        case DXGI_FORMAT_R10G10B10A2_UNORM:
            // The application creates the HDR10 signal.
            colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;
            break;

        case DXGI_FORMAT_R16G16B16A16_FLOAT:
            // The system creates the HDR10 signal; application uses linear values.
            colorSpace = DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709;
            break;

        default:
            break;
        }
    }

    m_colorSpace = colorSpace;

    UINT colorSpaceSupport = 0;
    if (SUCCEEDED(m_swapChain->CheckColorSpaceSupport(colorSpace, &colorSpaceSupport))
        && (colorSpaceSupport & DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT))
    {
        ThrowIfFailed(m_swapChain->SetColorSpace1(colorSpace));
    }
}
#pragma endregion

#pragma region WindowSet
// 이 메서드는 XAML 컨트롤이 생성 또는 재생성될 때 호출됩니다.
void DX::DeviceResources::SetSwapChainPanel(winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
{    
    if (!panel.IsLoaded())
        return; 

    GetSwapchainPanel() = panel;            
    m_logicalSize = winrt::Windows::Foundation::Size(static_cast<float>(panel.ActualWidth()), static_cast<float>(panel.ActualHeight()));
    //m_nativeOrientation = currentDisplayInformation.NativeOrientation();
    //m_currentOrientation = currentDisplayInformation.CurrentOrientation();
    m_compositionScaleX = panel.CompositionScaleX();
    m_compositionScaleY = panel.CompositionScaleY();    
    m_RasterizationScale = static_cast<float>(panel.XamlRoot().RasterizationScale());
    m_d2dContext->SetDpi(m_dpi, m_dpi);

    CreateWindowSizeDependentResources();  
}

// This method is called when the CoreWindow is created (or re-created).
void DeviceResources::SetWindow(HWND window, float width, float height) noexcept
{
    //auto windowPtr = static_cast<::IUnknown*>(winrt::get_abi(window));
    //m_window = windowPtr;
    m_window = window;
    //m_logicalSize = winrt::Windows::Foundation::Size(window.Bounds().Width, window.Bounds().Height);
    m_logicalSize = winrt::Windows::Foundation::Size(width, height);
    //DisplayInformation currentDisplayInformation = DisplayInformation::GetForCurrentView();
    //m_nativeOrientation = currentDisplayInformation.NativeOrientation();
    //m_currentOrientation = currentDisplayInformation.CurrentOrientation();
    //m_RasterizationScale = currentDisplayInformation.LogicalDpi();
    //m_d2dContext->SetDpi(m_RasterizationScale, m_RasterizationScale);

    CreateWindowSizeDependentResources();
}
#pragma endregion

#pragma region ValidateDevice
// This method is called in the event handler for the DisplayContentsInvalidated event.
void DeviceResources::ValidateDevice()
{
    // The D3D Device is no longer valid if the default adapter changed since the device
    // was created or if the device has been removed.

    DXGI_ADAPTER_DESC previousDesc;
    {
        com_ptr_nothrow<IDXGIAdapter1> previousDefaultAdapter;
        ThrowIfFailed(m_dxgiFactory->EnumAdapters1(0, previousDefaultAdapter.addressof()));

        ThrowIfFailed(previousDefaultAdapter->GetDesc(&previousDesc));
    }

    DXGI_ADAPTER_DESC currentDesc;
    {
        com_ptr_nothrow<IDXGIFactory2> currentFactory;
        ThrowIfFailed(CreateDXGIFactory2(m_dxgiFactoryFlags, IID_PPV_ARGS(currentFactory.addressof())));

        com_ptr_nothrow<IDXGIAdapter1> currentDefaultAdapter;
        ThrowIfFailed(currentFactory->EnumAdapters1(0, currentDefaultAdapter.addressof()));

        ThrowIfFailed(currentDefaultAdapter->GetDesc(&currentDesc));
    }

    // If the adapter LUIDs don't match, or if the device reports that it has been removed,
    // a new D3D device must be created.

    if (previousDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart
        || previousDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart
        || FAILED(m_d3dDevice->GetDeviceRemovedReason()))
    {
#ifdef _DEBUG
        OutputDebugStringA("Device Lost on ValidateDevice\n");
#endif

        // Create a new device and swap chain.
        HandleDeviceLost();
    }
}

// Recreate all device resources and set them back to the current state.
void DeviceResources::HandleDeviceLost()
{
    if (m_deviceNotify)
    {
        m_deviceNotify->OnDeviceLost();
    }

    m_d3dDepthStencilView.reset();
    m_d3dRenderTargetView.reset();
    m_renderTarget.reset();
    m_depthStencil.reset();
    m_swapChain.reset();
    m_d3dContext.reset();
    m_d3dDevice.reset();
    m_dxgiFactory.reset();
    //m_d2dFactory.reset();
    m_d2dFactory = nullptr;
    m_d2dDevice.reset();
    m_d2dContext.reset();
    m_d2dTargetBitmap.reset();

#if defined(_DEBUG)
    {
        com_ptr_nothrow<IDXGIDebug1> dxgiDebug;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiDebug.addressof()))))
        {
            dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
        }
    }
#endif

    CreateDeviceResources();
    m_d2dContext->SetDpi(m_dpi, m_dpi);
    CreateWindowSizeDependentResources();

    if (m_deviceNotify)
    {
        m_deviceNotify->OnDeviceRestored();
    }
}
#pragma endregion


#pragma region AppRenderingState
// Call this method when the app suspends. It provides a hint to the driver that the app
// is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
void DeviceResources::Trim() noexcept
{
    com_ptr_nothrow<IDXGIDevice3> dxgiDevice;
    if (SUCCEEDED(m_d3dDevice.query_to(dxgiDevice.addressof())))
    {
        dxgiDevice->Trim();
    }
}

// Present the contents of the swap chain to the screen.
void DeviceResources::Present()
{
    HRESULT hr = E_FAIL;
    if (m_options & c_AllowTearing)
    {
        // Recommended to always use tearing if supported when using a sync interval of 0.
        hr = m_swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
    }
    else
    {
        // The first argument instructs DXGI to block until VSync, putting the application
        // to sleep until the next VSync. This ensures we don't waste any cycles rendering
        // frames that will never be displayed to the screen.
        hr = m_swapChain->Present(1, 0);
    }

    // Discard the contents of the render target.
    // This is a valid operation only when the existing contents will be entirely
    // overwritten. If dirty or scroll rects are used, this call should be removed.
    if(m_d3dRenderTargetView)
        m_d3dContext->DiscardView(m_d3dRenderTargetView.get());

    if (m_d3dDepthStencilView)
    {
        // Discard the contents of the depth stencil.
        m_d3dContext->DiscardView(m_d3dDepthStencilView.get());
    }

    // If the device was removed either by a disconnection or a driver upgrade, we
    // must recreate all device resources.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
#ifdef _DEBUG
        char buff[64] = {};
        sprintf_s(buff, "Device Lost on Present: Reason code 0x%08X\n",
            static_cast<unsigned int>((hr == DXGI_ERROR_DEVICE_REMOVED) ? m_d3dDevice->GetDeviceRemovedReason() : hr));
        OutputDebugStringA(buff);
#endif
        HandleDeviceLost();
    }
    else
    {
        ThrowIfFailed(hr);

        if (!m_dxgiFactory->IsCurrent())
        {
            // Output information is cached on the DXGI Factory. If it is stale we need to create a new factory.
            ThrowIfFailed(CreateDXGIFactory2(m_dxgiFactoryFlags, IID_PPV_ARGS(m_dxgiFactory.put())));
        }
    }
}
#pragma endregion

#pragma region WindowTransform
// This method is called when the window changes size
bool DX::DeviceResources::SetLogicalSize(winrt::Windows::Foundation::Size logicalSize)
{
    if (m_logicalSize == logicalSize)
    {
        // Handle color space settings for HDR
        UpdateColorSpace();
        return false;
    }
    m_logicalSize = logicalSize;
    CreateWindowSizeDependentResources();

    return true;
}

bool DX::DeviceResources::SetSwapchainXamlChanged(double rasterizationScale, winrt::Windows::Foundation::Size logicalSize, float compositionScaleX, float compositionScaleY)
{
    bool needChange = false;    
    if (static_cast<float>(rasterizationScale) != m_RasterizationScale)
    {
        m_RasterizationScale = static_cast<float>(rasterizationScale);
        m_dpi *= m_RasterizationScale;
        m_d2dContext->SetDpi(m_dpi, m_dpi);
        needChange = true;
    }

    if (m_logicalSize != logicalSize)
    {
        m_logicalSize = winrt::Windows::Foundation::Size(logicalSize.Width, logicalSize.Height);
        needChange = true;
    }

    if (m_compositionScaleX != compositionScaleX ||
        m_compositionScaleY != compositionScaleY)
    {
        m_compositionScaleX = compositionScaleX;
        m_compositionScaleY = compositionScaleY;
        needChange = true;
    }

    if(needChange)
        CreateWindowSizeDependentResources();

    return needChange;
}

void DX::DeviceResources::SetCurrentOrientation(winrt::Windows::Graphics::Display::DisplayOrientations currentOrientation)
{
    if (m_currentOrientation != currentOrientation)
    {
        m_currentOrientation = currentOrientation;
        CreateWindowSizeDependentResources();
    }
}

// 이 메서드는 CompositionScaleChanged 이벤트의 이벤트 처리기에서 호출됩니다.
void DX::DeviceResources::SetCompositionScale(float compositionScaleX, float compositionScaleY)
{
    if (m_options & c_UseXAML)
    {
        if (m_compositionScaleX != compositionScaleX ||
            m_compositionScaleY != compositionScaleY)
        {
            m_compositionScaleX = compositionScaleX;
            m_compositionScaleY = compositionScaleY;
            CreateWindowSizeDependentResources();
        }
    }
}

DXGI_MODE_ROTATION DX::DeviceResources::ComputeDisplayRotation()
{
    DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

    // 참고: NativeOrientation은 DisplayOrientations 열거형이 다른 값을 포함하더라도
    // Landscape 또는 Portrait만 될 수 있습니다.
    //switch (m_nativeOrientation)
    //{
    //case DisplayOrientations::Landscape:
    //    switch (m_currentOrientation)
    //    {
    //    case DisplayOrientations::Landscape:
    //        rotation = DXGI_MODE_ROTATION_IDENTITY;
    //        break;

    //    case DisplayOrientations::Portrait:
    //        rotation = DXGI_MODE_ROTATION_ROTATE270;
    //        break;

    //    case DisplayOrientations::LandscapeFlipped:
    //        rotation = DXGI_MODE_ROTATION_ROTATE180;
    //        break;

    //    case DisplayOrientations::PortraitFlipped:
    //        rotation = DXGI_MODE_ROTATION_ROTATE90;
    //        break;
    //    }
    //    break;

    //case DisplayOrientations::Portrait:
    //    switch (m_currentOrientation)
    //    {
    //    case DisplayOrientations::Landscape:
    //        rotation = DXGI_MODE_ROTATION_ROTATE90;
    //        break;

    //    case DisplayOrientations::Portrait:
    //        rotation = DXGI_MODE_ROTATION_IDENTITY;
    //        break;

    //    case DisplayOrientations::LandscapeFlipped:
    //        rotation = DXGI_MODE_ROTATION_ROTATE270;
    //        break;

    //    case DisplayOrientations::PortraitFlipped:
    //        rotation = DXGI_MODE_ROTATION_ROTATE180;
    //        break;
    //    }
    //    break;
    //}
    return rotation;
}

void DeviceResources::UpdateRenderTargetSize()
{
    m_effectiveRasterizationScale = m_RasterizationScale;
    if (m_options & c_UseXAML)
    {
        m_effectiveCompositionScaleX = m_compositionScaleX;
        m_effectiveCompositionScaleY = m_compositionScaleY;
    }

    // 고해상도 디바이스에서 배터리 수명을 개선하려면 더 작은 렌더링 대상으로 렌더링하고
    // 출력이 표현될 때 GPU에서 출력의 크기를 조정할 수 있도록 허용합니다.
    if (!DisplayMetrics::SupportHighResolutions && m_RasterizationScale > DisplayMetrics::DpiThreshold)
    {
        float width = m_logicalSize.Width * m_RasterizationScale;
        float height = m_logicalSize.Height * m_RasterizationScale;

        // 디바이스가 세로 방향이면 높이가 너비보다 큽니다. 큰 치수는
        // 너비 임계값과 비교하고 작은 치수는
        // 높이 임계값과 비교합니다.
        if (max(width, height) > DisplayMetrics::WidthThreshold && min(width, height) > DisplayMetrics::HeightThreshold)
        {
            // 앱의 크기를 조정하기 위해 유효 DPI를 변경합니다. 논리 크기는 변경되지 않습니다.
            m_effectiveRasterizationScale /= 2.0f;
            if (m_options & c_UseXAML)
            {
                m_effectiveCompositionScaleX /= 2.0f;
                m_effectiveCompositionScaleY /= 2.0f;
            }
        }
    }

    // 필요한 렌더링 대상 크기를 픽셀 단위로 계산합니다.
    m_outputSize.Width = m_logicalSize.Width * m_effectiveRasterizationScale;
    m_outputSize.Height = m_logicalSize.Height * m_effectiveRasterizationScale;

    // DirectX 콘텐츠 크기를 0으로 만들지 않습니다.
    m_outputSize.Width = max(m_outputSize.Width, 1.0f);
    m_outputSize.Height = max(m_outputSize.Height, 1.0f);
}
#pragma endregion


