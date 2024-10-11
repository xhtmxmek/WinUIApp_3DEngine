#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
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

#pragma region ValidateDevice
				virtual void ValidateDevice() = 0;
				virtual void HandleDeviceLost() = 0;
#pragma endregion
				//void RegisterDeviceNotify(IDeviceNotify* deviceNotify) noexcept { _deviceNotify = deviceNotify; }

				virtual void GetHardwareAdapter(IDXGIAdapter1** ppAdapter) = 0;
				virtual void UpdateColorSpace() = 0;


#pragma region Clear
			public:
				virtual void ClearContext() = 0;
			private:
				/*Call this method when the app suspends. It provides a hint to the driver that the app
				is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
				Present the contents of the swap chain to the screen.
				*/
				virtual void Trim() noexcept = 0;
#pragma endregion
			public:
				virtual void Present() = 0;


#pragma region WindowTransform
				void SetLogicalResolution(SharedTypes::Size logicalSize);
				SharedTypes::Size GetResoulution() const { return _finalResolution; }
				//DXGI_MODE_ROTATION GetRotation() const noexcept { return m_rotation; }
				SharedTypes::Size GetLogicalResolution() const { return _logicalResolution; }
				float SetDpi(float dpi)
				{
					_dpi = dpi;
				}

				void OnWindowTransformChanged(const WindowParam& param);
				virtual void WindowTransformChanged_Internal(const WindowParam& WindowParam) = 0;
				virtual void SetCurrentOrientation(Engine::DisplayOrientation currentOrientation) = 0;
				virtual void SetCompositionScale(float compositionScaleX, float compositionScaleY) = 0;
#ifdef WIN_APPS_SDK				
				//void SetWindow(HWND window, float width, float height) noexcept;
#endif
#pragma endregion

#pragma region BackBuffer
				SceneColorFormat BackBufferFormat()
				{
					return _backBufferFormat;
				}

				unsigned int BackBufferCount()
				{
					return _backBufferCount;
				}				
#pragma endregion

#pragma region deviceAccesors
				//Option Set
				void                    AddOption(unsigned int option) { _options |= option; }
				void					RemoveOption(unsigned int option) { _options &= ~option; }
				unsigned int GetOptions() { return _options; }
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

#pragma region StateObject
				virtual shared_ptr<RHIDepthStencilState> CreateRHIDepthStencilState() = 0;
#pragma endregion


#pragma region Initialize
			public:
				virtual void PostInitialize() = 0;
			private:
				virtual void CreateDeviceIndependentResources() = 0;
				virtual void CreateDeviceResources() = 0;
				virtual void CreateWindowSizeDependentResources() = 0;
#pragma endregion

			private:
				unsigned int _backBufferCount;
				SceneColorFormat _backBufferFormat;
				SharedTypes::Size _backBufferSize;
				SharedTypes::Size _finalResolution;
				SharedTypes::Size _logicalResolution;
				DisplayOrientation _nativeOrientation;
				DisplayOrientation _currentOrientation;
				float _rasterizationScale;
				float _dpi;
				float _compositionScaleX;
				float _compositionScaleY;
				float _effectiveRasterizationScale;
				float _effectiveCompositionScaleX;
				float _effectiveCompositionScaleY;

				unsigned int _options;

				// The IDeviceNotify can be held directly as it owns the DeviceResources.
				//IDeviceNotify* _deviceNotify;
			};

			class DeviceResourcesUtil
			{
			public:
				static DeviceResourcesUtil& GetInstance()
				{
					static DeviceResourcesUtil instance;
					return instance;
				}
				void CreateDeviceResources();
				void ReleaseInstance() { _deviceResources.reset(); }

				static std::weak_ptr<DeviceResources> GetDeviceResources()
				{
					std::weak_ptr<DeviceResources> ptr(GetInstance()._deviceResources);
					return ptr;
				}
			private:
				std::shared_ptr<DeviceResources> _deviceResources;
			};
		}
	}
}

