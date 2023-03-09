#pragma once

#include "MainWindow.g.h"
//#include <d3d11_4.h>
//#include <dxgi1_6.h>
//#include <d2d1_3.h>
//#include "Bookstore.BookstoreViewModel.h"

namespace Engine
{
	class EngineCoreWrapper;
}

namespace winrt::AuthoringTool::implementation
{
	struct MainWindow : MainWindowT<MainWindow>
	{
		MainWindow();

		//int32_t MyProperty();
		//void MyProperty(int32_t value);

		void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
		void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
		AuthoringTool::BookstoreViewModel MainViewModel();
		AuthoringTool::ActorViewModel SelectedActorViewModel();
	private:
		//not projection
		void OnRendering(IInspectable const& sender, IInspectable const& args);
		
		void OnVisibilityChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs const& args);
		void OnActivated(IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
		void OnClosed(IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& args);
		void OnSizeChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args);
		
		void OnSwapChainPanelXamlRootChanged(Microsoft::UI::Xaml::XamlRoot const& sender, Microsoft::UI::Xaml::XamlRootChangedEventArgs const& args);
		void OnSwapChainPanelCompositionScaleChanged(Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender, IInspectable const& args);
		void OnSwapChainPanel_SizeChanged(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& args);
		
		//void OnSwapChainPanelSizeChanged(IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
		//void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation const& sender, IInspectable const& args);
		//void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation const& sender, IInspectable const& args);
		void OnSwapchainPanelLoaded(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
		
		void AppBarButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);
		
		void OnPointerPressedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnPointerMovedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnPointerReleasedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);
		void OnPointerWheelChangedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args);

		void SetPickedActor(EngineInterface_WRC::ActorProxy const& pickedActor);

		void OnKeyDown_SwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);
		void OnKeyUp_SwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args);		

		//Control		
		void RegisterDedicatedInputOnSwapchain();

		void GetPickedActor();

		//DXGI_MODE_ROTATION ComputeDisplayRotation() const noexcept
		//{
		//	DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

		//	switch (m_nativeOrientation)
		//	{
		//	case DisplayOrientations::Landscape:
		//		switch (m_currentOrientation)
		//		{
		//		case DisplayOrientations::Landscape:
		//			rotation = DXGI_MODE_ROTATION_IDENTITY;
		//			break;

		//		case DisplayOrientations::Portrait:
		//			rotation = DXGI_MODE_ROTATION_ROTATE270;
		//			break;

		//		case DisplayOrientations::LandscapeFlipped:
		//			rotation = DXGI_MODE_ROTATION_ROTATE180;
		//			break;

		//		case DisplayOrientations::PortraitFlipped:
		//			rotation = DXGI_MODE_ROTATION_ROTATE90;
		//			break;
		//		}
		//		break;

		//	case DisplayOrientations::Portrait:
		//		switch (m_currentOrientation)
		//		{
		//		case DisplayOrientations::Landscape:
		//			rotation = DXGI_MODE_ROTATION_ROTATE90;
		//			break;

		//		case DisplayOrientations::Portrait:
		//			rotation = DXGI_MODE_ROTATION_IDENTITY;
		//			break;

		//		case DisplayOrientations::LandscapeFlipped:
		//			rotation = DXGI_MODE_ROTATION_ROTATE270;
		//			break;

		//		case DisplayOrientations::PortraitFlipped:
		//			rotation = DXGI_MODE_ROTATION_ROTATE180;
		//			break;
		//		}
		//		break;
		//	}

		//	return rotation;
		//}

		//inline int ConvertDipsToPixels(float dips) const noexcept
		//{
		//	return int(dips * m_DPI / 96.f + 0.5f);
		//}

		//inline double ConvertPixelsToDips(int pixels) const noexcept
		//{
		//	return (double(pixels) * 96.f / m_DPI);
		//}

		// XAML 페이지 백그라운드에서 DirectX 콘텐츠를 렌더링하는 데 사용되는 리소스입니다.		
		winrt::EngineInterface_WRC::EngineInterface renderingEngine_;		

		bool					m_windowVisible;
		float                   m_logicalWidth;
		float                   m_logicalHeight;

		//winrt::Windows::Graphics::Display::DisplayOrientations	m_nativeOrientation;
		//winrt::Windows::Graphics::Display::DisplayOrientations	m_currentOrientation;

		// 백그라운드 작업자 스레드에서 독립 입력을 추적합니다.
		Windows::Foundation::IAsyncAction m_inputLoopWorker;

		//구현이 애플리케이션과 동일한 프로젝트(컴파일 단위)에 있으므로 std::nullptr_t로 초기화 후
		//winrt::make로 생성자에서 생성할수있음
		//AuthoringTool::BookstoreViewModel m_mainViewModel{ nullptr };
		//아니면 균일한생성
		AuthoringTool::BookstoreViewModel m_mainViewModel;
		AuthoringTool::ActorViewModel actorViewModel_;
	};
}

namespace winrt::AuthoringTool::factory_implementation
{
	struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
	{
	};
}
