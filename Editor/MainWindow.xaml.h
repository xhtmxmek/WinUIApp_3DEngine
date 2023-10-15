#pragma once

#include "MainWindow.g.h"
//#include "Bookstore.BookstoreViewModel.h"

namespace Engine
{
	class EngineCore;
}

namespace SharedTypes
{
	struct SwapchainPanelInfo;
}

namespace winrt::Editor::implementation
{
	struct MainWindow : MainWindowT<MainWindow>
	{

	public:
		MainWindow();
		winrt::Editor::WorldInfoViewModel WorldInfo();
		void TestFunc(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const& e);
	private:
		//not projection
		//void OnRendering(IInspectable const& sender, IInspectable const& args);

		void OnVisibilityChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs const& args);
		void OnActivated(IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
		void OnClosed(IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& args);
		void OnSizeChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args);

		void OnSwapChainPanelXamlRootChanged(Microsoft::UI::Xaml::XamlRoot const& sender, Microsoft::UI::Xaml::XamlRootChangedEventArgs const& args);
		void OnSwapChainPanelCompositionScaleChanged(Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender, IInspectable const& args);
		void OnSwapChainPanel_SizeChanged(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& args);
		void SetSwapchainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel, 
			SharedTypes::SwapchainPanelInfo& swapchainInfo_);

		//void OnSwapChainPanelSizeChanged(IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
		//void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation const& sender, IInspectable const& args);
		//void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation const& sender, IInspectable const& args);
		void OnSwapchainPanelLoaded(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		void AppBarButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

		void OnPointerPressedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnPointerMovedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnPointerReleasedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnPointerWheelChangedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);

		//void SetPickedActor(EngineInterface_WRC::ActorProxy const& pickedActor);

		void OnKeyDown_SwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);
		void OnKeyUp_SwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);

		//Control		
		void RegisterDedicatedInputOnSwapchain();
		void RegisterNativeSwapchain();

		//Scene
		void GetPickedActor();
	private:
		//Xaml Proxy
		winrt::Editor::WorldInfoViewModel worldInfo_;

		//inline int ConvertDipsToPixels(float dips) const noexcept
		//{
		//	return int(dips * m_DPI / 96.f + 0.5f);
		//}

		//inline double ConvertPixelsToDips(int pixels) const noexcept
		//{
		//	return (double(pixels) * 96.f / m_DPI);
		//}

		Engine::EngineCore* renderingEngine_;

		bool					m_windowVisible;
		float                   m_logicalWidth;
		float                   m_logicalHeight;

		//winrt::Windows::Graphics::Display::DisplayOrientations	m_nativeOrientation;
		//winrt::Windows::Graphics::Display::DisplayOrientations	m_currentOrientation;

		// 백그라운드 작업자 스레드에서 독립 입력을 추적합니다.
		Windows::Foundation::IAsyncAction m_inputLoopWorker;
	};
}

namespace winrt::Editor::factory_implementation
{
	struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
	{
	};
}
