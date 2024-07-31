#pragma once

#include "Renderer/Resource/DeviceResources.h"
namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			class DX11DeviceResources : public DeviceResources
			{

				DX11DeviceResources(DX11DeviceResources&&) = delete;
				DX11DeviceResources& operator= (DX11DeviceResources&&) = delete;

				DX11DeviceResources(DX11DeviceResources const&) = delete;
				DX11DeviceResources& operator= (DX11DeviceResources const&) = delete;

			public:
#pragma region Initialize
				virtual void CreateDeviceIndependentResources() override;
				virtual void CreateDeviceResources() override;
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

			private:
				virtual void GetHardwareAdapter(IDXGIAdapter1** ppAdapter);  
				virtual void UpdateColorSpace();                             

				//Window Transform Helper
				void                    UpdateRenderTargetSize();                       //Render Target Size ���
				DXGI_MODE_ROTATION      ComputeDisplayRotation();                       //Device�� ���� Rotation ���

			private:
				// Direct3D objects.                
				wil::com_ptr_nothrow<IDXGIFactory2> _dxgiFactory;
				wil::com_ptr_nothrow<ID3D11Device3> _d3dDevice;
				wil::com_ptr_nothrow<ID3D11DeviceContext2> _d3dContext;
				std::vector<wil::com_ptr_nothrow<ID3D11DeviceContext2>> deferredContexts_;
				wil::com_ptr_nothrow<IDXGISwapChain3> _swapChain;

				// Direct3D rendering objects. Required for 3D.
				wil::com_ptr_nothrow<ID3D11Texture2D> _backBufferTarget;
				wil::com_ptr_nothrow<ID3D11Texture2D>  _depthStencil;
				wil::com_ptr_nothrow<ID3D11RenderTargetView> _d3dRenderTargetView;
				wil::com_ptr_nothrow<ID3D11DepthStencilView> _d3dDepthStencilView;
				D3D11_VIEWPORT _screenViewport;

				// Direct3D properties.
				DXGI_FORMAT       _backBufferFormat;
				DXGI_FORMAT       _depthBufferFormat;
				UINT              _backBufferCount;
				D3D_FEATURE_LEVEL _d3dMinFeatureLevel;

				// Direct2D rendering object
				Microsoft::WRL::ComPtr<ID2D1Factory3>	_dFactory;
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