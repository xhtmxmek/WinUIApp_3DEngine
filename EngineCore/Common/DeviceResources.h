//
// DeviceResources.h - A wrapper for the Direct3D 11 device and swapchain
//

#pragma once
//using namespace winrt;
//#include <wrl.h>
//#include <wrl/client.h>
//#include <wil/cppwinrt.h>
//#include <wil/com.h>
using namespace wil;

namespace Engine
{
	//UI�� �����ִ� ����ü�鸸 ���� ��Ƴ��°͵� ������

	namespace DX
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

			DeviceResources(DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM,
				DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT,
				UINT backBufferCount = 2,
				D3D_FEATURE_LEVEL minFeatureLevel = D3D_FEATURE_LEVEL_9_3,
				unsigned int flags = 0) noexcept;

			~DeviceResources() = default;

			DeviceResources(DeviceResources&&) = delete;
			DeviceResources& operator= (DeviceResources&&) = delete;

			DeviceResources(DeviceResources const&) = delete;
			DeviceResources& operator= (DeviceResources const&) = delete;

			//Window Set
			//xaml ����						
			void SetSwapChainPanel(SwapchainPanelInfo const& panel);
			//corewindow ����
			//void SetWindow(winrt::Windows::UI::Core::CoreWindow const& window) noexcept;
			void SetWindow(HWND window, float width, float height) noexcept;

			//Validate Device
			void ValidateDevice();
			void HandleDeviceLost();
			void RegisterDeviceNotify(IDeviceNotify* deviceNotify) noexcept { m_deviceNotify = deviceNotify; }  //IdeviceNotiFy�� �Լ� ȣ��(�̰�쿡�� Engine)

			//App Ȱ��ȭ ����(Suspend | Rendring) 
			//device�� Trim�� DXDevice�� �������� �������� ���� �Ҵ��س��� �ӽù��۵��� �߶�Y�� �޸� Ȯ��(���� �����ɶ��� ��Ծ����)
			void Trim() noexcept;
			void Present();

			//Window Transform
			bool SetLogicalSize(SharedTypes::Size logicalSize);
			bool SetSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo);
			void SetCurrentOrientation(Engine::DisplayOrientation currentOrientation);
			void SetCompositionScale(float compositionScaleX, float compositionScaleY);

			//Get Size Value
			//RECT GetOutputSize() const noexcept { return m_outputSize; }				
			SharedTypes::Size GetOutputSize() const { return m_outputSize; }
			DXGI_MODE_ROTATION GetRotation() const noexcept { return m_rotation; }
			//// ������ ����� ũ��(DIP)�Դϴ�.
			SharedTypes::Size GetLogicalSize() const { return m_logicalSize; }
			//float						GetDpi() const { return m_effectiveDpi; }

			// Device Accessors.
			// Direct3D Accessors.
			auto                    GetD3DDevice() const noexcept { return m_d3dDevice.get(); }
			auto                    GetD3DDeviceContext() const noexcept { return m_d3dContext.get(); }
			auto                    GetSwapChain() const noexcept { return m_swapChain.get(); }
			auto                    GetDXGIFactory() const noexcept { return m_dxgiFactory.get(); }
			D3D_FEATURE_LEVEL       GetDeviceFeatureLevel() const noexcept { return m_d3dFeatureLevel; }
			ID3D11Texture2D* GetRenderTarget() const noexcept { return m_renderTarget.get(); }
			ID3D11Texture2D* GetDepthStencil() const noexcept { return m_depthStencil.get(); }
			ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return m_d3dRenderTargetView.get(); }
			ID3D11DepthStencilView* GetDepthStencilView() const noexcept { return m_d3dDepthStencilView.get(); }
			DXGI_FORMAT             GetBackBufferFormat() const noexcept { return m_backBufferFormat; }
			DXGI_FORMAT             GetDepthBufferFormat() const noexcept { return m_depthBufferFormat; }
			D3D11_VIEWPORT          GetScreenViewport() const noexcept { return m_screenViewport; }
			UINT                    GetBackBufferCount() const noexcept { return m_backBufferCount; }
			DirectX::XMFLOAT4X4     GetOrientationTransform3D() const noexcept { return m_orientationTransform3D; }
			DXGI_COLOR_SPACE_TYPE   GetColorSpace() const noexcept { return m_colorSpace; }
			unsigned int            GetDeviceOptions() const noexcept { return m_options; }

			// D2D �������Դϴ�.
			ID2D1Factory3* GetD2DFactory() const { return m_d2dFactory.Get(); }
			ID2D1Device2* GetD2DDevice() const { return m_d2dDevice.get(); }
			ID2D1DeviceContext2* GetD2DDeviceContext() const { return m_d2dContext.get(); }
			ID2D1Bitmap1* GetD2DTargetBitmap() const { return m_d2dTargetBitmap.get(); }
			IDWriteFactory3* GetDWriteFactory() const { return m_dwriteFactory.get(); }
			IWICImagingFactory2* GetWicImagingFactory() const { return m_wicFactory.get(); }
			D2D1::Matrix3x2F		GetOrientationTransform2D() const { return m_orientationTransform2D; }


			//Option Set
			void                    SetOption(unsigned int option) { m_options |= option; }
			// XAML �гο� ���� ĳ�õ� �����Դϴ�.
			//winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel& GetSwapchainPanel()
			//{
			//	static winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel swapchainPanel;
			//	return swapchainPanel;
			//}


		private:
			//Resource ������ helper
			void                    GetHardwareAdapter(IDXGIAdapter1** ppAdapter);  //DeviceResource ������ �ʿ��� hardware adapter get �Լ�
			void                    UpdateColorSpace();                             //HDR ���� �˻��Ͽ� swapChain�� colorSpace Set

			//Window Transform Helper
			void                    UpdateRenderTargetSize();                       //Render Target Size ���
			DXGI_MODE_ROTATION      ComputeDisplayRotation();                       //Device�� ���� Rotation ���

			//CreateResource
			void CreateDeviceIndependentResources();
			void CreateDeviceResources();
			void CreateWindowSizeDependentResources();

			// Direct3D objects.                
			wil::com_ptr_nothrow<IDXGIFactory2>           m_dxgiFactory;
			wil::com_ptr_nothrow<ID3D11Device3>           m_d3dDevice;
			wil::com_ptr_nothrow<ID3D11DeviceContext2>    m_d3dContext;
			wil::com_ptr_nothrow<IDXGISwapChain3>         m_swapChain;

			// Direct3D rendering objects. Required for 3D.
			wil::com_ptr_nothrow<ID3D11Texture2D>         m_renderTarget;
			wil::com_ptr_nothrow<ID3D11Texture2D>         m_depthStencil;
			wil::com_ptr_nothrow<ID3D11RenderTargetView>	m_d3dRenderTargetView;
			wil::com_ptr_nothrow<ID3D11DepthStencilView>	m_d3dDepthStencilView;
			D3D11_VIEWPORT                                  m_screenViewport;

			// Direct3D properties.
			DXGI_FORMAT                                     m_backBufferFormat;
			DXGI_FORMAT                                     m_depthBufferFormat;
			UINT                                            m_backBufferCount;
			D3D_FEATURE_LEVEL                               m_d3dMinFeatureLevel;

			// Direct2D rendering object
			Microsoft::WRL::ComPtr<ID2D1Factory3>		    m_d2dFactory;
			wil::com_ptr_nothrow<ID2D1Device2>		        m_d2dDevice;
			wil::com_ptr<ID2D1DeviceContext2>	            m_d2dContext;
			wil::com_ptr_nothrow<ID2D1Bitmap1>		        m_d2dTargetBitmap;

			// DirectWrite rendering object
			wil::com_ptr_nothrow<IDWriteFactory3>		    m_dwriteFactory;
			wil::com_ptr_nothrow<IWICImagingFactory2>	    m_wicFactory;

			// Cached device properties.
			//::IUnknown*                                                     m_window;
			HWND                                                            m_window;
			D3D_FEATURE_LEVEL                                               m_d3dFeatureLevel;
			DXGI_MODE_ROTATION                                              m_rotation;
			DWORD                                                           m_dxgiFactoryFlags;
			//RECT                                                          m_outputSize;        
			SharedTypes::Size												m_d3dRenderTargetSize;
			SharedTypes::Size												m_outputSize;
			SharedTypes::Size												m_logicalSize;
			DisplayOrientation												m_nativeOrientation;
			DisplayOrientation												m_currentOrientation;
			float											                m_RasterizationScale;
			float                                                           m_dpi;
			float											                m_compositionScaleX;
			float											                m_compositionScaleY;

			//// �ۿ��� ���ػ� ȭ���� �����ϴ��� ���θ� ����ϴ� �����Դϴ�.
			float											                m_effectiveRasterizationScale;
			float											                m_effectiveCompositionScaleX;
			float											                m_effectiveCompositionScaleY;

			// Transforms used for display orientation.
			D2D1::Matrix3x2F	                                            m_orientationTransform2D;
			DirectX::XMFLOAT4X4                                             m_orientationTransform3D;

			// HDR Support
			DXGI_COLOR_SPACE_TYPE                                           m_colorSpace;

			// DeviceResources options (see flags above)
			unsigned int                                                    m_options;

			// The IDeviceNotify can be held directly as it owns the DeviceResources.
			IDeviceNotify* m_deviceNotify;
			std::function<void(IDXGISwapChain3*)>							RegisterSwapChainToUIPanelCallBack;
		};

		class DeviceResourcesUtil
		{
		public:
			void CreateDeviceResources() { if (!m_deviceResources) m_deviceResources = std::make_shared<DeviceResources>(); }
			void ReleaseInstance() { m_deviceResources.reset(); }
			static DeviceResourcesUtil& GetInstance()
			{
				static DeviceResourcesUtil instance;
				return instance;
			}

			static std::shared_ptr<DeviceResources> GetDeviceResources() { return GetInstance().m_deviceResources; }



		private:
			DeviceResourcesUtil() = default;
			std::shared_ptr<DeviceResources>    m_deviceResources;
		};
	}
}

