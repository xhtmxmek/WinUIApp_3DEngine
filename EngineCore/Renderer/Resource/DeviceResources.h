//
// DeviceResources.h - A wrapper for the Direct3D 11 device and swapchain
//

#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			// Provides an interface for an application that owns DeviceResources to be notified of the device being lost or created.
			interface IDeviceNotify
			{
				virtual void OnDeviceLost() = 0;
				virtual void OnDeviceRestored() = 0;

			protected:
				~IDeviceNotify() = default;
			};

			// Controls all the DirectX device resources.
			class DeviceResources
			{
			public:
				static constexpr unsigned int c_AllowTearing = 0x1;
				static constexpr unsigned int c_EnableHDR = 0x2;
				static constexpr unsigned int c_UseXAML = 0x3;
				static unsigned int test;

				DeviceResources(SceneColorFormat backBufferFormat = SceneColorFormat::b8r8g8a8_unorm,
					SceneColorFormat depthBufferFormat = SceneColorFormat::d24_s8_uint,
					UINT backBufferCount = 2,					
					unsigned int flags = 0) noexcept;

				~DeviceResources() = default;

				DeviceResources(DeviceResources&&) = delete;
				DeviceResources& operator= (DeviceResources&&) = delete;

				DeviceResources(DeviceResources const&) = delete;
				DeviceResources& operator= (DeviceResources const&) = delete;

				//Validate Device
				virtual void ValidateDevice() = 0;
				virtual void HandleDeviceLost() = 0;
				void RegisterDeviceNotify(IDeviceNotify* deviceNotify) noexcept { _deviceNotify = deviceNotify; }

				virtual void GetHardwareAdapter(IDXGIAdapter1** ppAdapter) = 0;  
				virtual void UpdateColorSpace() = 0;                             


				/*Call this method when the app suspends. It provides a hint to the driver that the app
				is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
				Present the contents of the swap chain to the screen.
				*/				 
				virtual void Trim() noexcept = 0;
				virtual void Present() = 0;

#pragma region WindowTransform
				bool SetLogicalResolution(SharedTypes::Size logicalSize);
				SharedTypes::Size GetResoulution() const { return _finalResolution; }
				//DXGI_MODE_ROTATION GetRotation() const noexcept { return m_rotation; }
				SharedTypes::Size GetLogicalResolution() const { return _logicalResolution; }
				//float						GetDpi() const { return m_effectiveDpi; }
#ifdef WIN_APPS_SDK
				//Window Set										
				virtual void SetSwapChainPanel(SwapchainPanelInfo const& panel);								

				void SetWindow(HWND window, float width, float height) noexcept;
				bool SetSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo);
				void SetCurrentOrientation(Engine::DisplayOrientation currentOrientation);
				void SetCompositionScale(float compositionScaleX, float compositionScaleY);
#endif
#pragma endregion				

#pragma region deviceAccesors
				//Option Set
				void                    SetOption(unsigned int option) { m_options |= option; }
				//winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel& GetSwapchainPanel()
				//{
				//	static winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel swapchainPanel;
				//	return swapchainPanel;
				//}
#pragma endregion
				//RenderState ����
				//void SetRenderState(const Renderer::RHI::RasterizerState& rs = Renderer::RHI::DefaultRasterizerState,
				//	const Renderer::RHI::SamplerState ss = Renderer::RHI::DefaultSamplerState,
				//	const Renderer::RHI::DepthStencilState ds = Renderer::RHI::DefaultDepthStencilState,
				//	const Renderer::RHI::BlendState bs = Renderer::RHI::DefaultBlendState);

			private:
				virtual void CreateDeviceIndependentResources() = 0;
				virtual void CreateDeviceResources() = 0;
				virtual void CreateWindowSizeDependentResources() = 0;
				
				SharedTypes::Size												_renderTargetSize;
				SharedTypes::Size												_finalResolution;
				SharedTypes::Size												_logicalResolution;
				DisplayOrientation												_nativeOrientation;
				DisplayOrientation												_currentOrientation;
				float											                _rasterizationScale;
				float                                                           _dpi;
				float											                _compositionScaleX;
				float											                _compositionScaleY;
				float											                _effectiveRasterizationScale;
				float											                _effectiveCompositionScaleX;
				float											                _effectiveCompositionScaleY;

				// DeviceResources options (see flags above)
				unsigned int                                                    m_options;

				// The IDeviceNotify can be held directly as it owns the DeviceResources.
				IDeviceNotify* _deviceNotify;
			};

			class DeviceResourcesUtil
			{
			public:
				void CreateDeviceResources() { if (!_deviceResources) _deviceResources = std::make_shared<DeviceResources>(); }
				void ReleaseInstance() { _deviceResources.reset(); }
				static DeviceResourcesUtil& GetInstance()
				{
					static DeviceResourcesUtil instance;
					return instance;
				}

				static std::shared_ptr<DeviceResources>& GetDeviceResources() { return GetInstance()._deviceResources; }

			private:
				DeviceResourcesUtil() = default;
				std::shared_ptr<DeviceResources>    _deviceResources;
			};
		}
	}	
}

