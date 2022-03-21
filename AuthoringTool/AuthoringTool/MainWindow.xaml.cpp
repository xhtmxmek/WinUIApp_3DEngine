#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace DX11Engine_WinUI3_WRC;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::AuthoringTool::implementation
{
    MainWindow::MainWindow()
        :m_windowVisible(false)
    {
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
        //currentDisplayInformation.OrientationChanged({ this, &MainPage::OnOrientationChanged });
        //DisplayInformation::DisplayContentsInvalidated({ this, &MainPage::OnDisplayContentsInvalidated });

        m_logicalWidth = Bounds().Width;
        m_logicalHeight = Bounds().Height;

        //xamlRoot.Content().rotation
        //m_nativeOrientation = currentDisplayInformation.NativeOrientation();
        //m_currentOrientation = currentDisplayInformation.CurrentOrientation();

        //int outputWidth = ConvertDipsToPixels(m_logicalWidth);
        //int outputHeight = ConvertDipsToPixels(m_logicalHeight);

        //DXGI_MODE_ROTATION rotation = ComputeDisplayRotation();

        //if (rotation == DXGI_MODE_ROTATION_ROTATE90 || rotation == DXGI_MODE_ROTATION_ROTATE270)
        //{
        //    std::swap(outputWidth, outputHeight);
        //}

        //auto factory = winrt::get_activation_factory<winrt::DX11Engine_WinUI3_WRC::EngineDX11>();        
        //m_Engine = factory.ActivateInstance<winrt::DX11Engine_WinUI3_WRC::EngineDX11>();
        //winrt::make_self<winrt::DX11Engine_WinUI3_WRC::EngineDX11>();              

    }

#pragma region WindowEvent
    void MainWindow::OnVisibilityChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs const& args)
    {
        if (swapChainPanel().IsLoaded())
        {
            m_windowVisible = args.Visible();
            if (m_windowVisible)
            {
                m_Engine.StartRenderLoop();
            }
            else
            {
                m_Engine.StopRenderLoop();
            }
        }
    }

    void MainWindow::OnActivated(IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs const& args)
    {
        if (args.WindowActivationState() == Microsoft::UI::Xaml::WindowActivationState::Deactivated)
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

    void MainWindow::OnClosed(IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& args)
    {
        Engine_Scoped_Lock lock(m_Engine.GetCriticalSection());
        m_Engine.StopRenderLoop();
        m_Engine = { nullptr };
    }

    void MainWindow::OnSizeChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args)
    {
    }
#pragma endregion


#pragma region SwapChainPanel Event
    void MainWindow::OnSwapChainPanelXamlRootChanged(Microsoft::UI::Xaml::XamlRoot const& sender, Microsoft::UI::Xaml::XamlRootChangedEventArgs const& args)
    {
        Engine_Scoped_Lock lock(m_Engine.GetCriticalSection());
        // Dpi가 Change되면 WindowSize도 같이 Change 되니까 Engine에 Dpi Changed                
        m_Engine.OnSwapchainXamlChanged(sender.RasterizationScale(), sender.Size(), swapChainPanel().CompositionScaleX(), swapChainPanel().CompositionScaleY());
    }

    void MainWindow::OnSwapChainPanelCompositionScaleChanged(Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender, IInspectable const& args)
    {
        Engine_Scoped_Lock lock(m_Engine.GetCriticalSection());
        m_Engine.OnSwapchainXamlChanged(sender.RasterizationScale(), Windows::Foundation::Size(m_logicalWidth, m_logicalHeight), swapChainPanel().CompositionScaleX(), swapChainPanel().CompositionScaleY());
        //m_deviceResources->SetCompositionScale(sender->CompositionScaleX, sender->CompositionScaleY);
        //m_main->CreateWindowSizeDependentResources();
        //m_Engine.UnLockEngineThread();
    }

    void MainWindow::OnSwapchainPanelLoaded(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        swapChainPanel().XamlRoot().Changed({ this, &MainWindow::OnSwapChainPanelXamlRootChanged });

        //swapChainPanel이 로드 된 뒤에 엔진을 초기화한다
        double scale = swapChainPanel().XamlRoot().RasterizationScale();

        m_Engine.Initialize(swapChainPanel());

        // 독립 입력 포인터 이벤트를 얻으려면 SwapChainPanel을 등록합니다.                
        auto controller = Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnDedicatedThread();
        bool test = controller.DispatcherQueue().TryEnqueue(Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [this]
            {
                // CoreIndependentInputSource는 어떤 스레드가 만들어지던 특정 디바이스 유형에 대한 포인터 이벤트가 발생됩니다.  
                uint32_t inputParam = (uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Mouse |
                    (uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Touch |
                    (uint32_t)Microsoft::UI::Input::InputPointerSourceDeviceKinds::Pen;

                Microsoft::UI::Input::InputPointerSource coreInput = swapChainPanel().CreateCoreIndependentInputSource(
                    static_cast<Microsoft::UI::Input::InputPointerSourceDeviceKinds>(inputParam)
                );

                // 백그라운드 스레드에서 발생할 포인터 이벤트를 등록합니다.
                coreInput.PointerPressed({ this, &MainWindow::OnPointerPressedSwapChain });
                coreInput.PointerMoved({ this, &MainWindow::OnPointerMovedSwapChain });
                coreInput.PointerReleased({ this, &MainWindow::OnPointerReleasedSwapChain });

            });

        m_Engine.StartRenderLoop();
    }
#pragma endregion

    void MainWindow::AppBarButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // 앱에 적합한 앱 바가 있으면 사용하세요. 앱 바를 디자인합니다.
        // 그리고 다음과 같이 이벤트 처리기를 채웁니다.
    }

    void MainWindow::OnPointerPressedSwapChain(Microsoft::UI::Input::InputPointerSource const& sender, Microsoft::UI::Input::PointerEventArgs const& e)
    {
        // 포인터를 누르면 포인터 이동 추적을 시작합니다.
        //m_Engine.StartTracking();
    }

    void MainWindow::OnPointerMovedSwapChain(Microsoft::UI::Input::InputPointerSource const& sender, Microsoft::UI::Input::PointerEventArgs const& e)
    {
        // 포인터 추적 코드를 업데이트합니다.
        //if (m_Engine.IsTracking())
        //{
        //    m_Engine.TrackingUpdate(e.CurrentPoint().Position().X);
        //}
    }

    void MainWindow::OnPointerReleasedSwapChain(Microsoft::UI::Input::InputPointerSource const& sender, Microsoft::UI::Input::PointerEventArgs const& e)
    {
        // 포인터가 해제되는 경우 추적 포인터 이동이 중지됩니다.
        //m_main->StopTracking();
    }

    //void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    //{
    //    myButton().Content(box_value(L"Clicked"));
    //}

    //int32_t MainWindow::MyProperty()
    //{
    //    throw hresult_not_implemented();
    //}

    //void MainWindow::MyProperty(int32_t /* value */)
    //{
    //    throw hresult_not_implemented();
    //}

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
        double test = myButton().XamlRoot().RasterizationScale();
        test = 0.0f;
    }
}
