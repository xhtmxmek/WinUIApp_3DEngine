// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#include "EngineCore.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Common/Math/TransformGroup.h"
#include <Input/VirtualKey.h>


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

		//Init�Լ��� ���� App���� ȣ���ϴ� ���·� ����
		//// ������ ���� �ֱ��� �̺�Ʈ ó���⸦ ����մϴ�.

		// ������ �̺�Ʈ
		VisibilityChanged({ this, &MainWindow::OnVisibilityChanged });
		Activated({ this, &MainWindow::OnActivated });
		Closed({ this, &MainWindow::OnClosed });
		SizeChanged({ this, &MainWindow::OnSizeChanged });

		// ���� ü�� �г� �̺�Ʈ(DX ��������)     
		swapChainPanel().Loaded({ this, &MainWindow::OnSwapchainPanelLoaded });
		swapChainPanel().CompositionScaleChanged({ this, &MainWindow::OnSwapChainPanelCompositionScaleChanged });
		worldOutlinerTree().ItemInvoked({ this, &MainWindow::OnActorTreeClicked });
		componentTree().ItemInvoked({ this, &MainWindow::OnComponentTreeClicked });
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

		splitViewPage().KeyDown({ this, &MainWindow::OnKeyDown_MainSplitView });
		splitViewPage().KeyUp({ this, &MainWindow::OnKeyUp_MainSplitView });

		renderingEngine_->StartRenderLoop();
		actorViewModel_.UpdateWorldInfoProxy();
	}
#pragma endregion

	void MainWindow::AppBarButton_Click(IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		// �ۿ� ������ �� �ٰ� ������ ����ϼ���. �� �ٸ� �������մϴ�.
		// �׸��� ������ ���� �̺�Ʈ ó���⸦ ä��ϴ�.
	}

	void MainWindow::OnPointerPressedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
	{
		Microsoft::UI::Input::PointerPoint pt = args.GetCurrentPoint(nullptr);
		auto pointerProperties = pt.Properties();
		vector<bool> buttonState = { pointerProperties.IsLeftButtonPressed(), pointerProperties.IsMiddleButtonPressed(), pointerProperties.IsRightButtonPressed() };
		renderingEngine_->PointerProcess(buttonState);
	}

	void MainWindow::OnPointerMovedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
	{
		Microsoft::UI::Input::PointerPoint pt = args.GetCurrentPoint(nullptr);
		Windows::Foundation::Point pos = pt.Position();
		renderingEngine_->PointerProcess(Vector2i((int)pos.X, (int)pos.Y));
	}

	void MainWindow::OnPointerReleasedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
	{
		Microsoft::UI::Input::PointerPoint pt = args.GetCurrentPoint(nullptr);
		auto pointerProperties = pt.Properties();
		vector<bool> buttonState = { pointerProperties.IsLeftButtonPressed(), pointerProperties.IsRightButtonPressed(), pointerProperties.IsMiddleButtonPressed() };
		renderingEngine_->PointerProcess(buttonState);
		//GetPickedActor();
	}

	void MainWindow::OnPointerWheelChangedSwapChain(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
	{
		Microsoft::UI::Input::PointerPoint pt = args.GetCurrentPoint(nullptr);
		auto pointerProperties = pt.Properties();
		renderingEngine_->PointerProcess(pointerProperties.MouseWheelDelta());

		// �����Ͱ� �����Ǵ� ��� ���� ������ �̵��� �����˴ϴ�.
		//m_main->StopTracking();
		//lbutton�� ��ŷ. buttonDown���� ��ġ�� ���� picking object �����Ѵٸ� ������Ʈ����������.
		//renderingEngine_.PointerWheelChanged(args);
	}

	void MainWindow::OnKeyDown_MainSplitView(Windows::Foundation::IInspectable const&, KeyRoutedEventArgs const& args)
	{
		renderingEngine_->KeyProcess(static_cast<SharedTypes::VirtualKey>(args.Key()), true);

		if (args.Key() == Windows::System::VirtualKey::Escape)
		{
			actorViewModel_.ClearSelectedActor(PropertyPanel());
		}
	}

	void MainWindow::OnKeyUp_MainSplitView(Windows::Foundation::IInspectable const&, KeyRoutedEventArgs const& args)
	{
		renderingEngine_->KeyProcess(static_cast<SharedTypes::VirtualKey>(args.Key()), false);

	}

	void MainWindow::OnActorTreeClicked(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const& e)
	{
		auto selectedItem = unbox_value_or<Editor::ActorLabel>(e.InvokedItem(), nullptr);
		if (selectedItem != nullptr)
		{
			actorViewModel_.UpdateSelectedActorDetail(selectedItem.Name(), PropertyPanel());
			auto height1 = splitViewPage().ActualHeight();
			height1 = WorldOutLiner().ActualHeight();
			height1 = DetailLabel().Height();
			height1 = componentTreeBorder().Height();
			double newScrollHeight = splitViewPage().ActualHeight() - WorldOutLiner().ActualHeight()
				- DetailLabel().Height() - componentTreeBorder().Height() - OutlinerCommentPanel().ActualHeight();
			PropertyScroll().Height(newScrollHeight);
		}
	}

	void MainWindow::OnComponentTreeClicked(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::Controls::TreeViewItemInvokedEventArgs const& e)
	{
		auto selectedItem = unbox_value_or<Editor::ComponentInfo>(e.InvokedItem(), nullptr);
		if (selectedItem != nullptr)
		{
			//actorViewModel_.SelectedActorDetail().UpdateSelectedComponent(selectedItem.Name());
			actorViewModel_.UpdateSelectedComponent(selectedItem.Name(), PropertyPanel());
			//Detail()
		}
	}

	void MainWindow::RegisterDedicatedInputOnSwapchain()
	{
		// ���� �Է� ������ �̺�Ʈ�� �������� SwapChainPanel�� ����մϴ�.                
		auto controller = Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnDedicatedThread();
		controller.DispatcherQueue().TryEnqueue(Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [this]
			{
				// CoreIndependentInputSource�� � �����尡 ��������� Ư�� ����̽� ������ ���� ������ �̺�Ʈ�� �߻��˴ϴ�.  
				uint32_t inputParam = (uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Mouse |
				(uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Touch |
			(uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Pen;

		Microsoft::UI::Input::InputPointerSource coreInput = swapChainPanel().CreateCoreIndependentInputSource(
			static_cast<Microsoft::UI::Input::InputPointerSourceDeviceKinds>(inputParam)
		);

		// ��׶��� �����忡�� �߻��� ������ �̺�Ʈ�� ����մϴ�.
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
}

