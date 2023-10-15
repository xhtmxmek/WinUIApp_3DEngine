// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#include "EngineCore.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif


#include "WorldInfoViewModel/TransformProperty.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Common/Math/TransformGroup.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Editor::implementation
{
	MainWindow::MainWindow()
		:m_windowVisible(false)
	{
		//m_mainViewModel = winrt::make<AuthoringTool::implementation::BookstoreViewModel>();
		InitializeComponent();

		//Init함수로 빼서 App에서 호출하는 형태로 하자
		//// 페이지 수명 주기의 이벤트 처리기를 등록합니다.

		// 윈도우 이벤트
		VisibilityChanged({ this, &MainWindow::OnVisibilityChanged });
		Activated({ this, &MainWindow::OnActivated });
		Closed({ this, &MainWindow::OnClosed });
		SizeChanged({ this, &MainWindow::OnSizeChanged });

		// 스왑 체인 패널 이벤트(DX 렌더링용)     
		swapChainPanel().Loaded({ this, &MainWindow::OnSwapchainPanelLoaded });
		swapChainPanel().CompositionScaleChanged({ this, &MainWindow::OnSwapChainPanelCompositionScaleChanged });
		worldOutlinerTree().ItemInvoked({this, &MainWindow::OnActorTreeClicked });
		m_logicalWidth = Bounds().Width;
		m_logicalHeight = Bounds().Height;
	}

	winrt::Editor::WorldInfoViewModel MainWindow::WorldInfo()
	{
		return actorViewModel_;
	}

#pragma region WindowEvent
	void MainWindow::OnVisibilityChanged(IInspectable const&, Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs const& args)
	{
		if (swapChainPanel().IsLoaded())
		{
			m_windowVisible = args.Visible();
			if (m_windowVisible)
				renderingEngine_->StartRenderLoop();
			else
				renderingEngine_->StopRenderLoop();
		}
	}

	void MainWindow::OnActivated(IInspectable const&, Microsoft::UI::Xaml::WindowActivatedEventArgs const& args)
	{
		if (args.WindowActivationState() == Microsoft::UI::Xaml::WindowActivationState::PointerActivated)
		{
			// Show the "paused" UI. 
			//VisualStateManager::GoToState(this, L"PauseUI", false);
		}
		else if (args.WindowActivationState() == Microsoft::UI::Xaml::WindowActivationState::Deactivated)
		{
			// Show the "active" UI. 
			//VisualStateManager.GoToState(this, "ActivateUI", false);
		}
	}

	void MainWindow::OnClosed(IInspectable const&, Microsoft::UI::Xaml::WindowEventArgs const&)
	{
		renderingEngine_->StopRenderLoop();
		renderingEngine_->UnInitialize();
		Engine::ReleaseEngine();
	}

	void MainWindow::OnSizeChanged(IInspectable const&, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const&)
	{
	}
#pragma endregion


#pragma region SwapChainPanel Event
	void MainWindow::OnSwapChainPanelXamlRootChanged(Microsoft::UI::Xaml::XamlRoot const&, Microsoft::UI::Xaml::XamlRootChangedEventArgs const&)
	{
		SharedTypes::SwapchainPanelInfo scPanelInfo;
		SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
		renderingEngine_->OnSwapchainXamlChanged(scPanelInfo);
	}

	void MainWindow::OnSwapChainPanelCompositionScaleChanged(Microsoft::UI::Xaml::Controls::SwapChainPanel const&, IInspectable const&)
	{
		SharedTypes::SwapchainPanelInfo scPanelInfo;
		SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
		renderingEngine_->OnSwapchainXamlChanged(scPanelInfo);
	}

	void MainWindow::OnSwapChainPanel_SizeChanged(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::SizeChangedEventArgs const&)
	{
		SharedTypes::SwapchainPanelInfo scPanelInfo;
		SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
		renderingEngine_->OnSwapchainXamlChanged(scPanelInfo);
	}

	void MainWindow::SetSwapchainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel,
		SharedTypes::SwapchainPanelInfo& swapchainInfo_)
	{
		SharedTypes::SwapchainPanelInfo swapchainpanelInfo;

		swapchainInfo_.ActureSize = SharedTypes::Size(panel.ActualSize().x, panel.ActualSize().y);
		swapchainInfo_.CompositionScale = Vector2f(panel.CompositionScaleX(), panel.CompositionScaleY());
		swapchainInfo_.IsLoaded = panel.IsLoaded();
		swapchainInfo_.RasterizationScale = panel.RasterizationScale();

	}

	void MainWindow::OnSwapchainPanelLoaded(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		//swapChainPanel().XamlRoot().Changed({ this, &MainWindow::OnSwapChainPanelXamlRootChanged });        
		swapChainPanel().SizeChanged({ this, &MainWindow::OnSwapChainPanel_SizeChanged });

		SharedTypes::SwapchainPanelInfo scPanelInfo;
		SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
		Engine::InitEngine();
		renderingEngine_ = Engine::GetRenderingEngine();
		renderingEngine_->Initialize(scPanelInfo);
		RegisterNativeSwapchain();
		//RegisterDedicatedInputOnSwapchain();

		//winrt::Windows::Foundation::Numerics::float2        
		swapChainPanel().PointerPressed({ this, &MainWindow::OnPointerPressedSwapChain });
		swapChainPanel().PointerReleased({ this, &MainWindow::OnPointerReleasedSwapChain });
		swapChainPanel().PointerMoved({ this, &MainWindow::OnPointerMovedSwapChain });
		swapChainPanel().PointerWheelChanged({ this, &MainWindow::OnPointerWheelChangedSwapChain });

		swapChainPanel().KeyDown({ this, &MainWindow::OnKeyDown_SwapChain });
		swapChainPanel().KeyUp({ this, &MainWindow::OnKeyUp_SwapChain });
		

		renderingEngine_->StartRenderLoop();
		actorViewModel_.UpdateWorldInfoProxy();
	}
#pragma endregion

	void MainWindow::AppBarButton_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		// 앱에 적합한 앱 바가 있으면 사용하세요. 앱 바를 디자인합니다.
		// 그리고 다음과 같이 이벤트 처리기를 채웁니다.
	}

	void MainWindow::OnPointerPressedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
	{
	}

	void MainWindow::OnPointerMovedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
	{
	}

	void MainWindow::OnPointerReleasedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
	{
		GetPickedActor();
	}

	void MainWindow::OnPointerWheelChangedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
	{
		// 포인터가 해제되는 경우 추적 포인터 이동이 중지됩니다.
		//m_main->StopTracking();
		//lbutton떄 피킹. buttonDown때와 위치가 같고 picking object 존재한다면 오브젝트보내버리기.
		//renderingEngine_.PointerWheelChanged(args);
	}

	void MainWindow::OnKeyDown_SwapChain(Windows::Foundation::IInspectable const&, KeyRoutedEventArgs const& args)
	{
		//renderingEngine_->KeyboardProcess(args);
		if (args.Key() == Windows::System::VirtualKey::Escape)
		{
			actorViewModel_.ClearSelectedActor();
		}
	}

	void MainWindow::OnKeyUp_SwapChain(Windows::Foundation::IInspectable const&, KeyRoutedEventArgs const&)
	{
		//renderingEngine_.KeyboardProcess(args);

	}

	void MainWindow::OnActorTreeClicked(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const& e)
	{
		auto selectedItem = unbox_value_or<Editor::ActorLabel>(e.InvokedItem(), nullptr);
		if (selectedItem != nullptr)
		{
			actorViewModel_.UpdateSelectedActorDetail(selectedItem.Name());
		}		
	}

	void MainWindow::RegisterDedicatedInputOnSwapchain()
	{
		// 독립 입력 포인터 이벤트를 얻으려면 SwapChainPanel을 등록합니다.                
		auto controller = Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnDedicatedThread();
		controller.DispatcherQueue().TryEnqueue(Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [this]
			{
				// CoreIndependentInputSource는 어떤 스레드가 만들어지던 특정 디바이스 유형에 대한 포인터 이벤트가 발생됩니다.  
				uint32_t inputParam = (uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Mouse |
				(uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Touch |
			(uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Pen;

		Microsoft::UI::Input::InputPointerSource coreInput = swapChainPanel().CreateCoreIndependentInputSource(
			static_cast<Microsoft::UI::Input::InputPointerSourceDeviceKinds>(inputParam)
		);

		// 백그라운드 스레드에서 발생할 포인터 이벤트를 등록합니다.
		//coreInput.PointerPressed({ this, &MainWindow::OnPointerPressedSwapChain });
		//coreInput.PointerMoved({ this, &MainWindow::OnPointerMovedSwapChain });
		//coreInput.PointerReleased({ this, &MainWindow::OnPointerReleasedSwapChain });
		//coreInput.PointerWheelChanged({ this, &MainWindow::OnPointerWheelChangedSwapChain });

			});
	}

	void MainWindow::RegisterNativeSwapchain()
	{
		swapChainPanel().DispatcherQueue().TryEnqueue(winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority::High,
			[this]
			{
				auto panelNative = swapChainPanel().as<ISwapChainPanelNative>();
			renderingEngine_->GetSwapChain();
			panelNative->SetSwapChain(renderingEngine_->GetSwapChain());
			});
	}

	void MainWindow::GetPickedActor()
	{
		//Test Code
		for (int i = 0; i < 5; i++)
		{
			hstring componentName = L"TestComponent_" + to_hstring(i);
		}
	}

}

