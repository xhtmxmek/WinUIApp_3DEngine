#include "pch.h"
#include "RendererBaseHeader.h"
#include "DX11Context.h"

#ifdef DX11_RHI

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{

            DXGI_FORMAT GetDxgiFormat(SceneColorFormat format)
            {
                
                switch (format)
                {
                    case SceneColorFormat::b8r8g8a8_unorm:
                    {
                        return DXGI_FORMAT_B8G8R8A8_UNORM;
                    }
                    case SceneColorFormat::d24_s8_uint:
                    {
                        return DXGI_FORMAT_D24_UNORM_S8_UINT;
                    }
                }
            }

#pragma region Initialize
            void DX11Context::CreateDeviceIndependentResources()
            {                
                D2D1_FACTORY_OPTIONS options;
                ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)                
                options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
                
                ThrowIfFailed(
                    DWriteCreateFactory(
                        DWRITE_FACTORY_TYPE_SHARED,
                        __uuidof(IDWriteFactory3),
                        (::IUnknown**)&_dwriteFactory
                    )
                );

                // Direct2D
                ThrowIfFailed(
                    D2D1CreateFactory(
                        D2D1_FACTORY_TYPE_SINGLE_THREADED,
                        __uuidof(ID2D1Factory3),
                        &options,
                        (void**)_d2dFactory.ReleaseAndGetAddressOf()
                    )
                );

                //WIC(Windows Imaging Component)

                ThrowIfFailed(
                    CoCreateInstance(
                        CLSID_WICImagingFactory2,
                        nullptr,
                        CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(_wicFactory.addressof())
                    )
                );
            }

            void DX11Context::CreateDeviceContext()
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
                    //OutputDebugstringA("WARNING: Direct3D Debug Device is not available\n");
                }
#endif

#ifdef _DEBUG
                {
                    wil::com_ptr<IDXGIInfoQueue> dxgiInfoQueue;
                    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.addressof()))))
                    {
                        _dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

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

                ThrowIfFailed(CreateDXGIFactory2(_dxgiFactoryFlags, IID_PPV_ARGS(_dxgiFactory.put())));

                // Determines whether tearing support is available for fullscreen borderless windows.
                if (GetOptions() & c_AllowTearing)
                {
                    BOOL allowTearing = FALSE;

                    wil::com_ptr<IDXGIFactory5> factory5;
                    _dxgiFactory.query_to(factory5.addressof());

                    //HRESULT hr = m_dxgiFactory.as(&factory5);
                    if (!factory5)
                    {
                        hr = factory5->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing));
                    }

                    if (FAILED(hr) || !allowTearing)
                    {
                        RemoveOption(c_AllowTearing);
#ifdef _DEBUG
                        //OutputDebugstringA("WARNING: Variable refresh rate displays not supported");
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
                    if (s_featureLevels[featLevelCount] < _d3dMinFeatureLevel)
                        break;
                }

                if (!featLevelCount)
                {
                    throw std::out_of_range("minFeatureLevel too high");
                }

                wil::com_ptr_nothrow<IDXGIAdapter1> adapter;
                GetHardwareAdapter(&adapter);

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
                        &_d3dFeatureLevel,         // Returns feature level of device created.
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
                        &_d3dFeatureLevel,
                        context.addressof()
                    );

                    if (SUCCEEDED(hr))
                    {
                        //OutputDebugstringA("Direct3D Adapter - WARP\n");
                    }
                }
#endif

                ThrowIfFailed(hr);


                int numThread = std::thread::hardware_concurrency();
                deferredContexts_.reserve(numThread);
                deferredContexts_.resize(numThread);
                for (auto deferredContext : deferredContexts_)
                {
                    wil::com_ptr_nothrow<ID3D11DeviceContext> newContext;
                    ThrowIfFailed(device->CreateDeferredContext(0, newContext.addressof()));
                    newContext.query_to(deferredContext.addressof());
                }

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

                ThrowIfFailed(device.query_to(&_d3dDevice));
                ThrowIfFailed(context.query_to(&_d3dContext));

                // Direct2D ����̽� ��ü �� �ش� ���ؽ�Ʈ�� ����ϴ�.
                wil::com_ptr_nothrow<IDXGIDevice3> dxgiDevice;
                ThrowIfFailed(
                    _d3dDevice.query_to(dxgiDevice.addressof())
                );

                ThrowIfFailed(
                    _d2dFactory->CreateDevice(dxgiDevice.get(), &_d2dDevice)
                );

                ThrowIfFailed(
                    _d2dDevice->CreateDeviceContext(
                        D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
                        &_d2dContext
                    )
                );

                float dpi;
                _d2dContext->GetDpi(&dpi, &dpi);
                SetDpi(dpi);
        }

            void DX11Context::CreateWindowSizeDependentResources()
            {
                ID3D11RenderTargetView* nullViews[] = { nullptr };
                _d3dContext->OMSetRenderTargets(static_cast<UINT>(std::size(nullViews)), nullViews, nullptr);
                _backBufferTexture = nullptr;
                _backBufferDepthStencilTexture = nullptr;
                _backBufferRenderTargetView = nullptr;
                _backBufferDepthStencilView = nullptr;
                _d3dContext->Flush();
                _d2dContext->SetTarget(nullptr);
                _d2dTargetBitmap = nullptr;

                UpdateBackBufferSize();

                //DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();
                // Determine the render target size in pixels.        
                //bool swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
                //m_d3dRenderTargetSize.Width = swapDimensions ? m_outputSize.Height : m_outputSize.Width;
                //m_d3dRenderTargetSize.Height = swapDimensions ? m_outputSize.Width : m_outputSize.Height;
                //_d3dRenderTargetSize.Width = m_outputSize.Width;
                //_d3dRenderTargetSize.Height = m_outputSize.Height;

                //const DXGI_FORMAT backBufferFormat = NoSRGB(m_backBufferFormat);
                //const UINT backBufferWidth = std::max<UINT>(static_cast<UINT>(m_d3dRenderTargetSize.Width), 1u);
                //const UINT backBufferHeight = std::max<UINT>(static_cast<UINT>(m_d3dRenderTargetSize.Height), 1u);

                if (_swapChain)
                {
                    // If the swap chain already exists, resize it.
                    HRESULT hr = _swapChain->ResizeBuffers(
                        BackBufferCount(),
                        lround(GetLogicalResolution().Width),
                        lround(GetLogicalResolution().Height),
                        GetDxgiFormat(BackBufferFormat()),
                        (GetOptions() & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u
                    );

                    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
                    {
#ifdef _DEBUG
                        char buff[64] = {};
                        sprintf_s(buff, "Device Lost on ResizeBuffers: Reason code 0x%08X\n",
                            static_cast<unsigned int>((hr == DXGI_ERROR_DEVICE_REMOVED) ? _d3dDevice->GetDeviceRemovedReason() : hr));
                        //OutputDebugstringA(buff);
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
                    //if (GetOptions() & c_UseXAML)
                    //    scaling = DisplayMetrics::SupportHighResolutions ? DXGI_SCALING_NONE : DXGI_SCALING_STRETCH;
                    //else
                    //    scaling = DisplayMetrics::SupportHighResolutions ? DXGI_SCALING_NONE : DXGI_SCALING_ASPECT_RATIO_STRETCH;
                    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
                    swapChainDesc.Width = (UINT)GetLogicalResolution().Width;
                    swapChainDesc.Height = (UINT)GetLogicalResolution().Height;
                    swapChainDesc.Format = GetDxgiFormat(BackBufferFormat());
                    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    swapChainDesc.BufferCount = BackBufferCount();
                    swapChainDesc.SampleDesc.Count = 1;
                    swapChainDesc.SampleDesc.Quality = 0;
                    swapChainDesc.Scaling = scaling;
                    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;       //DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
                    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
                    swapChainDesc.Flags = (GetOptions() & c_AllowTearing) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0u;
                    

                    wil::com_ptr_nothrow<IDXGISwapChain1> swapChain;
                    if (GetOptions() & c_UseXAML)
                    {
                        // XAML interop
                        ThrowIfFailed(
                            _dxgiFactory->CreateSwapChainForComposition(
                                _d3dDevice.get(),
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
                        ThrowIfFailed(_dxgiFactory->CreateSwapChainForHwnd(
                            _d3dDevice.get(),
                            _window,
                            &swapChainDesc,
                            &fsSwapChainDesc,
                            nullptr,
                            swapChain.addressof()
                        ));
                    }

                    ThrowIfFailed(swapChain.query_to(&_swapChain));

                    //auto panelNative = m_swapchainPanel.as<ISwapChainPanelNative>();
                    //panelNative->SetSwapChain(m_swapChain.Get());


                    if (GetOptions() & c_UseXAML)
                    {
                        // Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
                        // ensures that the application will only render after each VSync, minimizing power consumption.
                        wil::com_ptr_nothrow<IDXGIDevice3> dxgiDevice;
                        ThrowIfFailed(_d3dDevice.query_to(&dxgiDevice));
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

                ThrowIfFailed(_swapChain->SetRotation(_rotation));
                
                if (GetOptions() & c_UseXAML)
                {
                    DXGI_MATRIX_3X2_F inverseScale = { 0 };
                    inverseScale._11 = 1.0f / GetEffectiveCompositionScale().Width;
                    inverseScale._22 = 1.0f / GetEffectiveCompositionScale().Height;
                    wil::com_ptr_nothrow<IDXGISwapChain2> spSwapChain2;
                    ThrowIfFailed(
                        _swapChain.query_to(spSwapChain2.addressof())
                    );

                    ThrowIfFailed(
                        spSwapChain2->SetMatrixTransform(&inverseScale)
                    );
                }

                // Create a render target view of the swap chain back buffer.
                ThrowIfFailed(_swapChain->GetBuffer(0, IID_PPV_ARGS(_backBufferTexture.put())));

                CD3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc(D3D11_RTV_DIMENSION_TEXTURE2D, _backBufferFormat);
                ThrowIfFailed(_d3dDevice->CreateRenderTargetView(
                    _backBufferTexture.get(),
                    &renderTargetViewDesc,
                    _backBufferRenderTargetView.put()
                ));

                if (_depthBufferFormat != DXGI_FORMAT_UNKNOWN)
                {
                    // Create a depth stencil view for use with 3D rendering if needed.
                    CD3D11_TEXTURE2D_DESC depthStencilDesc(
                        _depthBufferFormat,
                        GetLogicalResolution().Width,
                        GetLogicalResolution().Height,
                        1, // This depth stencil view has only one texture.
                        1, // Use a single mipmap level.
                        D3D11_BIND_DEPTH_STENCIL
                    );

                    ThrowIfFailed(_d3dDevice->CreateTexture2D(
                        &depthStencilDesc,
                        nullptr,
                        _backBufferDepthStencilTexture.put()
                    ));

                    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
                    ThrowIfFailed(_d3dDevice->CreateDepthStencilView(
                        _backBufferDepthStencilTexture.get(),
                        &depthStencilViewDesc,
                        _backBufferDepthStencilView.addressof()
                    ));
                }

                // Set the 3D rendering viewport to target the entire window.
                _screenViewport = CD3D11_VIEWPORT(
                    0.0f,
                    0.0f,
                    static_cast<float>(GetLogicalResolution().Width),
                    static_cast<float>(GetLogicalResolution().Height)
                );

                D2D1_BITMAP_PROPERTIES1 bitmapProperties =
                    D2D1::BitmapProperties1(
                        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
                        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                        (float)GetRasterizationScale(),
                        (float)GetRasterizationScale()
                    );

                wil::com_ptr_nothrow<IDXGISurface2> dxgiBackBuffer;
                ThrowIfFailed(
                    _swapChain->GetBuffer(0, IID_PPV_ARGS(dxgiBackBuffer.addressof()))
                );

                ThrowIfFailed(
                    _d2dContext->CreateBitmapFromDxgiSurface(
                        dxgiBackBuffer.get(),
                        &bitmapProperties,
                        _d2dTargetBitmap.put()
                    )
                );

                _d2dContext->SetTarget(_d2dTargetBitmap.get());
                _d2dContext->SetDpi(GetDpi() * GetEffectiveRasterizationScale(), GetDpi() * GetEffectiveRasterizationScale());

                _d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
            }
#pragma endregion

#pragma region ValidateDevice
            void DX11Context::ValidateDevice()
            {
                // The D3D Device is no longer valid if the default adapter changed since the device
    // was created or if the device has been removed.

                DXGI_ADAPTER_DESC previousDesc;
                {
                    wil::com_ptr_nothrow<IDXGIAdapter1> previousDefaultAdapter;
                    ThrowIfFailed(_dxgiFactory->EnumAdapters1(0, previousDefaultAdapter.addressof()));

                    ThrowIfFailed(previousDefaultAdapter->GetDesc(&previousDesc));
                }

                DXGI_ADAPTER_DESC currentDesc;
                {
                    wil::com_ptr_nothrow<IDXGIFactory2> currentFactory;
                    ThrowIfFailed(CreateDXGIFactory2(_dxgiFactoryFlags, IID_PPV_ARGS(currentFactory.addressof())));

                    wil::com_ptr_nothrow<IDXGIAdapter1> currentDefaultAdapter;
                    ThrowIfFailed(currentFactory->EnumAdapters1(0, currentDefaultAdapter.addressof()));

                    ThrowIfFailed(currentDefaultAdapter->GetDesc(&currentDesc));
                }

                // If the adapter LUIDs don't match, or if the device reports that it has been removed,
                // a new D3D device must be created.

                if (previousDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart
                    || previousDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart
                    || FAILED(_d3dDevice->GetDeviceRemovedReason()))
                {
#ifdef _DEBUG
                    //OutputDebugstringA("Device Lost on ValidateDevice\n");
#endif

        // Create a new device and swap chain.
                    HandleDeviceLost();
                }
            }

            void DX11Context::HandleDeviceLost()
            {
                //if (m_deviceNotify)
                //{
                //    m_deviceNotify->OnDeviceLost();
                //}

                _backBufferRenderTargetView.reset();
                _backBufferDepthStencilView.reset();
                _backBufferTexture.reset();
                _backBufferDepthStencilTexture.reset();
                _swapChain.reset();
                _d3dContext.reset();
                _d3dDevice.reset();
                _dxgiFactory.reset();
                //m_d2dFactory.reset();
                _d2dFactory = nullptr;
                _d2dDevice.reset();
                _d2dContext.reset();
                _d2dTargetBitmap.reset();

#if defined(_DEBUG)
                {
                    wil::com_ptr_nothrow<IDXGIDebug1> dxgiDebug;
                    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiDebug.addressof()))))
                    {
                        dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
                    }
                }
#endif

                CreateDeviceContext();
                _d2dContext->SetDpi(GetDpi(), GetDpi());
                CreateWindowSizeDependentResources();

                //if (m_deviceNotify)
                //{
                //    m_deviceNotify->OnDeviceRestored();
                //}
            }
#pragma endregion

#pragma region AppRenderingState
            void DX11Context::Trim()
            {
                wil::com_ptr_nothrow<IDXGIDevice3> dxgiDevice;
                if (SUCCEEDED(_d3dDevice.query_to(dxgiDevice.addressof())))
                {
                    dxgiDevice->Trim();
                }
            }

            void DX11Context::Present()
            {
                HRESULT hr = E_FAIL;
                if (GetOptions() & c_AllowTearing)
                {
                    // Recommended to always use tearing if supported when using a sync interval of 0.
                    hr = _swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
                }
                else
                {
                    // The first argument instructs DXGI to block until VSync, putting the application
                    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
                    // frames that will never be displayed to the screen.
                    hr = _swapChain->Present(1, 0);
                }

                // Discard the contents of the render target.
                // This is a valid operation only when the existing contents will be entirely
                // overwritten. If dirty or scroll rects are used, this call should be removed.
                if (_backBufferRenderTargetView)
                    _d3dContext->DiscardView(_backBufferRenderTargetView.get());

                if (_backBufferDepthStencilView)
                {
                    // Discard the contents of the depth stencil.
                    _d3dContext->DiscardView(_backBufferDepthStencilView.get());
                }

                // If the device was removed either by a disconnection or a driver upgrade, we
                // must recreate all device resources.
                if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
                {
#ifdef _DEBUG
                    char buff[64] = {};
                    sprintf_s(buff, "Device Lost on Present: Reason code 0x%08X\n",
                        static_cast<unsigned int>((hr == DXGI_ERROR_DEVICE_REMOVED) ? _d3dDevice->GetDeviceRemovedReason() : hr));
                    //OutputDebugstringA(buff);
#endif
                    HandleDeviceLost();
                }
                else
                {
                    ThrowIfFailed(hr);

                    if (!_dxgiFactory->IsCurrent())
                    {
                        // Output information is cached on the DXGI Factory. If it is stale we need to create a new factory.
                        ThrowIfFailed(CreateDXGIFactory2(_dxgiFactoryFlags, IID_PPV_ARGS(_dxgiFactory.put())));
                    }
                }
            }
#pragma endregion

            void DX11Context::ClearContext()
            {
                _d3dContext->ClearState();
                Trim();                
            }

            void DX11Context::UpdateBackBufferSize()
            {
                m_effectiveRasterizationScale = m_RasterizationScale;
                if (m_options & c_UseXAML)
                {
                    m_effectiveCompositionScaleX = m_compositionScaleX;
                    m_effectiveCompositionScaleY = m_compositionScaleY;
                }

                // ���ػ� ����̽����� ���͸� ������ �����Ϸ��� �� ���� ������ ������� �������ϰ�
                // ����� ǥ���� �� GPU���� ����� ũ�⸦ ������ �� �ֵ��� ����մϴ�.
                if (!DisplayMetrics::SupportHighResolutions && m_RasterizationScale > DisplayMetrics::DpiThreshold)
                {
                    float width = m_logicalSize.Width * m_RasterizationScale;
                    float height = m_logicalSize.Height * m_RasterizationScale;

                    // ����̽��� ���� �����̸� ���̰� �ʺ񺸴� Ů�ϴ�. ū ġ����
                    // �ʺ� �Ӱ谪�� ���ϰ� ���� ġ����
                    // ���� �Ӱ谪�� ���մϴ�.
                    if (max(width, height) > DisplayMetrics::WidthThreshold && min(width, height) > DisplayMetrics::HeightThreshold)
                    {
                        // ���� ũ�⸦ �����ϱ� ���� ��ȿ DPI�� �����մϴ�. ��� ũ��� ������� �ʽ��ϴ�.
                        m_effectiveRasterizationScale /= 2.0f;
                        if (m_options & c_UseXAML)
                        {
                            m_effectiveCompositionScaleX /= 2.0f;
                            m_effectiveCompositionScaleY /= 2.0f;
                        }
                    }
                }

                // �ʿ��� ������ ��� ũ�⸦ �ȼ� ������ ����մϴ�.
                m_outputSize.Width = m_logicalSize.Width * m_effectiveRasterizationScale;
                m_outputSize.Height = m_logicalSize.Height * m_effectiveRasterizationScale;

                // DirectX ������ ũ�⸦ 0���� ������ �ʽ��ϴ�.
                m_outputSize.Width = max(m_outputSize.Width, 1.0f);
                m_outputSize.Height = max(m_outputSize.Height, 1.0f);
            }

            void DeviceContext::SetCurrentOrientation(Engine::DisplayOrientation currentOrientation)
            {
                if (m_currentOrientation != currentOrientation)
                {
                    m_currentOrientation = currentOrientation;
                    CreateWindowSizeDependentResources();
                }
            }

            // �� �޼���� CompositionScaleChanged �̺�Ʈ�� �̺�Ʈ ó���⿡�� ȣ��˴ϴ�.
            void DeviceContext::SetCompositionScale(const SharedTypes::Size& compositionScale)
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

            void DeviceContext::PostInitialize()
            {
                CreateWindowSizeDependentResources();
            }

            void DeviceContext::GetHardwareAdapter(IDXGIAdapter1** ppAdapter)
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
                        //OutputDebugstringW(buff);
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
                        //OutputDebugstringW(buff);
#endif

                        break;
                    }
                }

                *ppAdapter = adapter.detach();
            }

            void DeviceContext::UpdateColorSpace()
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
           
            void DeviceContext::SetSwapChainPanel(WindowParam const& panelInfo)
            {
                if (!panelInfo.IsLoaded)
                    return;

                //UI���̾�        
                m_logicalSize = panelInfo.ActureSize;
                //m_nativeOrientation = currentDisplayInformation.NativeOrientation();
                //m_currentOrientation = currentDisplayInformation.CurrentOrientation();
                m_compositionScaleX = panelInfo.CompositionScale.x;
                m_compositionScaleY = panelInfo.CompositionScale.y;
                m_RasterizationScale = panelInfo.RasterizationScale;
                m_d2dContext->SetDpi(m_dpi, m_dpi);

                CreateWindowSizeDependentResources();
            }

            // This method is called when the CoreWindow is created (or re-created).
            void DeviceContext::SetWindow(HWND window, float width, float height) noexcept
            {
                //auto windowPtr = static_cast<::IUnknown*>(winrt::get_abi(window));
                //m_window = windowPtr;
                m_window = window;
                //m_logicalSize = winrt::Windows::Foundation::Size(window.Bounds().Width, window.Bounds().Height);
                m_logicalSize = SharedTypes::Size(width, height);
                //DisplayInformation currentDisplayInformation = DisplayInformation::GetForCurrentView();
                //m_nativeOrientation = currentDisplayInformation.NativeOrientation();
                //m_currentOrientation = currentDisplayInformation.CurrentOrientation();
                //m_RasterizationScale = currentDisplayInformation.LogicalDpi();
                //m_d2dContext->SetDpi(m_RasterizationScale, m_RasterizationScale);

                CreateWindowSizeDependentResources();
            }
            void Renderer::RHI::DX11Context::PostInitialize()
            {
            }
}
	}
}

#endif