#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			class DeviceContext
			{
			public:
				static constexpr unsigned int c_AllowTearing = 0x1;
				static constexpr unsigned int c_EnableHDR = 0x2;
				static constexpr unsigned int c_UseXAML = 0x3;
				static unsigned int test;

				DeviceContext(SceneColorFormat backBufferFormat = SceneColorFormat::b8r8g8a8_unorm,
					SceneColorFormat depthBufferFormat = SceneColorFormat::d24_s8_uint,
					UINT backBufferCount = 2,
					unsigned int flags = 0) noexcept;

				~DeviceContext() = default;

				DeviceContext(DeviceContext&&) = delete;
				DeviceContext& operator= (DeviceContext&&) = delete;

				DeviceContext(DeviceContext const&) = delete;
				DeviceContext& operator= (DeviceContext const&) = delete;

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
				const SharedTypes::Size& GetResoulution() const { return _finalResolution; }
				//DXGI_MODE_ROTATION GetRotation() const noexcept { return m_rotation; }
				const SharedTypes::Size& GetLogicalResolution() const { return _logicalResolution; }

				const SharedTypes::Size& GetCompositionScale()
				{
					return _compositionScale;
				}

				const SharedTypes::Size& GetEffectiveCompositionScale()
				{
					return _effectiveCompositionScale;
				}

				const float GetRasterizationScale()
				{
					return _rasterizationScale;
				}

				const float GetEffectiveRasterizationScale()
				{
					return _effectiveRasterizationScale;
				}

				const float GetDpi()
				{
					return _dpi;
				}

				float SetDpi(float dpi)
				{
					_dpi = dpi;
				}
				
				virtual void SetCurrentOrientation(Engine::DisplayOrientation currentOrientation) = 0;
				virtual void SetCompositionScale(const SharedTypes::Size& compositionScale)
				{
					_compositionScale = compositionScale;
				}
				void SetEffectiveCompositionScale(const SharedTypes::Size& compositionScale)
				{
					_effectiveCompositionScale = compositionScale;
				}
				void OnWindowTransformChanged(const WindowParam& param);
#pragma endregion

#pragma region BackBuffer
			public:
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
			public:
				void                    AddOption(unsigned int option) { _options |= option; }
				void					RemoveOption(unsigned int option) { _options &= ~option; }
				unsigned int GetOptions() { return _options; }
				//winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel& GetSwapchainPanel()
				//{
				//	static winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel swapchainPanel;
				//	return swapchainPanel;
				//}
#pragma endregion
				//RenderState
				//void SetRenderState(const Renderer::RHI::RasterizerState& rs = Renderer::RHI::DefaultRasterizerState,
				//	const Renderer::RHI::SamplerState ss = Renderer::RHI::DefaultSamplerState,
				//	const Renderer::RHI::DepthStencilState ds = Renderer::RHI::DefaultDepthStencilState,
				//	const Renderer::RHI::BlendState bs = Renderer::RHI::DefaultBlendState);

#pragma region StateObject
				virtual shared_ptr<RHIDepthStencilState> CreateRHIDepthStencilState(const DepthStencilDesc& Desc) = 0;
#pragma endregion


#pragma region Initialize
			public:
				virtual void PostInitialize() = 0;
			private:
				virtual void CreateDeviceIndependentResources() = 0;
				virtual void CreateDeviceContext() = 0;
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
				SharedTypes::Size _compositionScale;
				SharedTypes::Size _effectiveCompositionScale;
				float _dpi;
				float _rasterizationScale;
				float _effectiveRasterizationScale;

				unsigned int _options;

				// The IDeviceNotify can be held directly as it owns the DeviceContext.
				//IDeviceNotify* _deviceNotify;
			};

			class DeviceContextWrapper
			{
			public:
				static DeviceContextWrapper& GetInstance()
				{
					static DeviceContextWrapper instance;
					return instance;
				}
				void CreateDeviceContext();
				void ReleaseInstance() { _DeviceContext.reset(); }

				static std::weak_ptr<DeviceContext> GetDeviceContext()
				{
					std::weak_ptr<DeviceContext> ptr(GetInstance()._DeviceContext);
					return ptr;
				}
			private:
				std::shared_ptr<DeviceContext> _DeviceContext;
			};
		}
	}
}

