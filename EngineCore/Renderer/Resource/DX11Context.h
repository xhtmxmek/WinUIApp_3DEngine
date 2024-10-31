#pragma once

#ifdef DX11_RHI

#include "Renderer/Resource/DeviceContext.h"
namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			// Helper class for COM exceptions
			class com_exception : public std::exception
			{
			public:
				com_exception(HRESULT hr) noexcept : result(hr) {}

				const char* what() const override
				{
					static char s_str[64] = {};
					sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
					return s_str;
				}

			private:
				HRESULT result;
			};

			inline void ThrowIfFailed(HRESULT hr)
			{
				if (FAILED(hr))
				{					
					throw com_exception(hr);
				}
			}

#if defined(_DEBUG)
			inline bool SdkLayersAvailable()
			{
				HRESULT hr = D3D11CreateDevice(
					nullptr,
					D3D_DRIVER_TYPE_NULL,       
					0,
					D3D11_CREATE_DEVICE_DEBUG,  
					nullptr,                    
					0,
					D3D11_SDK_VERSION,          
					nullptr,                    
					nullptr,                    
					nullptr                     
				);

				return SUCCEEDED(hr);
			}
#endif



			class DX11Context : public DeviceContext
			{				
			public:
				DX11Context() = default;

				DX11Context(DX11Context&&) = delete;
				DX11Context& operator= (DX11Context&&) = delete;

				DX11Context(DX11Context const&) = delete;
				DX11Context& operator= (DX11Context const&) = delete;
#pragma region Initialize
			public:
				virtual void PostInitialize() override;
				virtual void CreateDeviceIndependentResources() override;
				virtual void CreateDeviceContext() override;
				virtual void CreateWindowSizeDependentResources() override;
#pragma endregion				

#pragma region device Accessors
				// Direct3D Accessors.
				//auto                    GetD3DDevice() const noexcept { return m_d3dDevice.get(); }
				//auto                    GetD3DDeviceContext() const noexcept { return m_d3dContext.get(); }
				//auto					GetDeferredContext(unsigned int index) const noexcept { return deferredContexts_[index].get(); }
				//auto                    GetSwapChain() const noexcept { return m_swapChain.get(); }
				//auto                    GetDXGIFactory() const noexcept { return m_dxgiFactory.get(); }
				//D3D_FEATURE_LEVEL       GetDeviceFeatureLevel() const noexcept { return m_d3dFeatureLevel; }
				//ID3D11Texture2D* GetRenderTarget() const noexcept { return m_renderTarget.get(); }
				//ID3D11Texture2D* GetDepthStencil() const noexcept { return m_depthStencil.get(); }
				//ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return m_d3dRenderTargetView.get(); }
				//ID3D11DepthStencilView* GetDepthStencilView() const noexcept { return m_d3dDepthStencilView.get(); }
				//DXGI_FORMAT             GetBackBufferFormat() const noexcept { return m_backBufferFormat; }
				//DXGI_FORMAT             GetDepthBufferFormat() const noexcept { return m_depthBufferFormat; }
				//D3D11_VIEWPORT          GetScreenViewport() const noexcept { return m_screenViewport; }
				//UINT                    GetBackBufferCount() const noexcept { return m_backBufferCount; }
				//DirectX::XMFLOAT4X4     GetOrientationTransform3D() const noexcept { return m_orientationTransform3D; }
				//DXGI_COLOR_SPACE_TYPE   GetColorSpace() const noexcept { return m_colorSpace; }
				//unsigned int            GetDeviceOptions() const noexcept { return m_options; }


				//ID2D1Factory3* GetD2DFactory() const { return m_d2dFactory.Get(); }
				//ID2D1Device2* GetD2DDevice() const { return m_d2dDevice.get(); }
				//ID2D1DeviceContext2* GetD2DDeviceContext() const { return m_d2dContext.get(); }
				//ID2D1Bitmap1* GetD2DTargetBitmap() const { return m_d2dTargetBitmap.get(); }
				//IDWriteFactory3* GetDWriteFactory() const { return m_dwriteFactory.get(); }
				//IWICImagingFactory2* GetWicImagingFactory() const { return m_wicFactory.get(); }
				//D2D1::Matrix3x2F		GetOrientationTransform2D() const { return m_orientationTransform2D; }
#pragma endregion

#pragma region ValidateDevice
				virtual void ValidateDevice() override;
				virtual void HandleDeviceLost() override;
#pragma endregion

#pragma region AppRenderingState
				virtual void Trim() noexcept final;
				virtual void Present() final;
#pragma endregion

				virtual void ClearContext();

#pragma region WindowTransform				
				virtual void SetCurrentOrientation(Engine::DisplayOrientation currentOrientation) {};
#pragma endregion


#pragma region PipelineStateObject
				virtual shared_ptr<RHIDepthStencilState> CreateRHIDepthStencilState(const DepthStencilDesc& Desc);
#pragma endregion

			private:
				virtual void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);  
				virtual void UpdateColorSpace();                             

				//Window Transform Helper
				void                    UpdateBackBufferSize();                       
				DXGI_MODE_ROTATION      ComputeDisplayRotation();                       

			private:
				// Direct3D objects.                
				wil::com_ptr_nothrow<IDXGIFactory2> _dxgiFactory;
				wil::com_ptr_nothrow<ID3D11Device3> _d3dDevice;
				wil::com_ptr_nothrow<ID3D11DeviceContext2> _d3dContext;
				std::vector<wil::com_ptr_nothrow<ID3D11DeviceContext2>> deferredContexts_;
				wil::com_ptr_nothrow<IDXGISwapChain3> _swapChain;

				// Direct3D rendering objects. Required for 3D.
				wil::com_ptr_nothrow<ID3D11Texture2D> _backBufferTexture;
				wil::com_ptr_nothrow<ID3D11Texture2D>  _backBufferDepthStencilTexture;
				wil::com_ptr_nothrow<ID3D11RenderTargetView> _backBufferRenderTargetView;
				wil::com_ptr_nothrow<ID3D11DepthStencilView> _backBufferDepthStencilView;
				D3D11_VIEWPORT _screenViewport;

				// Direct3D properties.
				DXGI_FORMAT       _backBufferFormat;
				DXGI_FORMAT       _depthBufferFormat;
				UINT              _backBufferCount;
				D3D_FEATURE_LEVEL _d3dMinFeatureLevel;

				// Direct2D rendering object				
				Microsoft::WRL::ComPtr<ID2D1Factory3>	_d2dFactory;
				wil::com_ptr_nothrow<ID2D1Device2>		_d2dDevice;
				wil::com_ptr<ID2D1DeviceContext2>	    _d2dContext;
				wil::com_ptr_nothrow<ID2D1Bitmap1>		_d2dTargetBitmap;

				// DirectWrite rendering object
				wil::com_ptr_nothrow<IDWriteFactory3>	 _dwriteFactory;
				wil::com_ptr_nothrow<IWICImagingFactory2> _wicFactory;

				// Cached device properties.				
				HWND               _window;
				D3D_FEATURE_LEVEL  _d3dFeatureLevel;
				DXGI_MODE_ROTATION _rotation;
				DWORD              _dxgiFactoryFlags;


				// Transforms used for display orientation.
				D2D1::Matrix3x2F	_orientationTransform2D;
				DirectX::XMFLOAT4X4 _orientationTransform3D;

				// HDR Support
				DXGI_COLOR_SPACE_TYPE _colorSpace;
			};
		}
	}
}
#endif