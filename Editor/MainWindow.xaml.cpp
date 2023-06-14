// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#include "Common/EngineBaseHeader.h"
#include "Common/EngineCommonHeader.h"
#include "EngineInterface.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

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

        //OnPointerPressedSwapChain
        //swapChainPanel().key
        //swapChainPanel().SizeChanged({ this, &MainWindow::OnSwapChainPanel_SizeChanged });


        // Retrieve the window handle (HWND) of the current WinUI 3 window.
        //auto windowNative{ this->try_as<::IWindowNative>() };
        //winrt::check_bool(windowNative);
        //HWND hWnd{ 0 };
        //windowNative->get_WindowHandle(&hWnd);        

        //winrt::Microsoft::UI::Xaml::Interop::native            
        //swapChainPanel().dragDragEnter({this, })
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
    }

#pragma region WindowEvent
    void MainWindow::OnVisibilityChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowVisibilityChangedEventArgs const& args)
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

    void MainWindow::OnActivated(IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs const& args)
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

    void MainWindow::OnClosed(IInspectable const& sender, Microsoft::UI::Xaml::WindowEventArgs const& args)
    {
        renderingEngine_->StopRenderLoop();
        renderingEngine_->UnInitialize();
        renderingEngine_ = { nullptr };
    }

    void MainWindow::OnSizeChanged(IInspectable const& sender, Microsoft::UI::Xaml::WindowSizeChangedEventArgs const& args)
    {
        //if (swapChainPanel().IsLoaded())
        //    renderingEngine_.OnWindowSizeChanged(args.Size());
    }
#pragma endregion


#pragma region SwapChainPanel Event
    void MainWindow::OnSwapChainPanelXamlRootChanged(Microsoft::UI::Xaml::XamlRoot const& sender, Microsoft::UI::Xaml::XamlRootChangedEventArgs const& args)
    {
        SharedTypes::SwapchainPanelInfo scPanelInfo;
        SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
        renderingEngine_->OnSwapchainXamlChanged(scPanelInfo);
    }

    void MainWindow::OnSwapChainPanelCompositionScaleChanged(Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender, IInspectable const& args)
    {
        SharedTypes::SwapchainPanelInfo scPanelInfo;
        SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
        renderingEngine_->OnSwapchainXamlChanged(scPanelInfo);
    }

    void MainWindow::OnSwapChainPanel_SizeChanged(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& args)
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

        swapchainInfo_.RegisterSwapChainToUIPanel = [&](IDXGISwapChain3* engineSwapChain) {

            panel.DispatcherQueue().TryEnqueue(winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority::High, 
                [&]
                {
                    auto panelNative = panel.as<ISwapChainPanelNative>();
                    IDXGISwapChain3* test = engineSwapChain;
                    panelNative->SetSwapChain(engineSwapChain);
                    //�̰� ȣ���ϴ� ������ �ᱹ �Ѵ� �˾ƾߵȴ�. ��Ե� 
                });
        };
    }

    void MainWindow::OnSwapchainPanelLoaded(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        //swapChainPanel().XamlRoot().Changed({ this, &MainWindow::OnSwapChainPanelXamlRootChanged });        
        swapChainPanel().SizeChanged({ this, &MainWindow::OnSwapChainPanel_SizeChanged });

        SharedTypes::SwapchainPanelInfo scPanelInfo;
        SetSwapchainPanelInfo(swapChainPanel(), scPanelInfo);
        renderingEngine_->Initialize(scPanelInfo);
        //RegisterDedicatedInputOnSwapchain();

        //winrt::Windows::Foundation::Numerics::float2        
        swapChainPanel().PointerPressed({ this, &MainWindow::OnPointerPressedSwapChain });
        swapChainPanel().PointerReleased({ this, &MainWindow::OnPointerReleasedSwapChain });
        swapChainPanel().PointerMoved({ this, &MainWindow::OnPointerMovedSwapChain });
        swapChainPanel().PointerWheelChanged({ this, &MainWindow::OnPointerWheelChangedSwapChain });

        swapChainPanel().KeyDown({ this, &MainWindow::OnKeyDown_SwapChain });
        swapChainPanel().KeyUp({ this, &MainWindow::OnKeyUp_SwapChain });

        renderingEngine_->StartRenderLoop();
        GetWorldInfo();
    }
#pragma endregion

    void MainWindow::AppBarButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        // �ۿ� ������ �� �ٰ� ������ ����ϼ���. �� �ٸ� �������մϴ�.
        // �׸��� ������ ���� �̺�Ʈ ó���⸦ ä��ϴ�.
    }

    void MainWindow::OnPointerPressedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {

        //TODO
        //���콺 ��ŷ�� ����
        //���콺 ������Ʈ ������Ʈ, 
        /*
        * -���۵��� ����
        * ���� Ŭ���� ��ŷ���� ������Ʈ�� ���� �̾ƿ�. ������Ʈ�� ������ EngineInterface�� �������.
        * EngineInterFace���� �˻��ؼ� ActorProxy ������. ���� ��ŷ �����ϸ� ActorProxy ��ȯ�ؼ� ActorViewModel�� �Ѱ���.
        * ViewModel����
        */
        //m_Engine.StartTracking();        
        //trackingOutput = renderingEngine_.startTracking();        
        //renderingEngine_.startT
        //renderingEngine_.StartTracking(args);
    }

    void MainWindow::OnPointerMovedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        // ������ ���� �ڵ带 ������Ʈ�մϴ�.
        //if (m_Engine.IsTracking())
        //{
        //    m_Engine.TrackingUpdate(e.CurrentPoint().Position().X);
        //}
        //renderingEngine_.TrackingUpdate(args);
    }

    void MainWindow::OnPointerReleasedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        //EngineInterface_WRC::PointerActionResult result = renderingEngine_.StopTracking(args);
        //EngineInterface_WRC::ActorProxy proxy;

        GetPickedActor();
        //proxy.Components().
        //result.PickedActor()
    }

    void MainWindow::OnPointerWheelChangedSwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args)
    {
        // �����Ͱ� �����Ǵ� ��� ���� ������ �̵��� �����˴ϴ�.
        //m_main->StopTracking();
        //lbutton�� ��ŷ. buttonDown���� ��ġ�� ���� picking object �����Ѵٸ� ������Ʈ����������.
        //renderingEngine_.PointerWheelChanged(args);
    }

    void MainWindow::OnKeyDown_SwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        //renderingEngine_->KeyboardProcess(args);
    }

    void MainWindow::OnKeyUp_SwapChain(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
    {
        //renderingEngine_.KeyboardProcess(args);
    }

    void MainWindow::RegisterDedicatedInputOnSwapchain()
    {
        // ���� �Է� ������ �̺�Ʈ�� �������� SwapChainPanel�� ����մϴ�.                
        auto controller = Microsoft::UI::Dispatching::DispatcherQueueController::CreateOnDedicatedThread();
        bool result = controller.DispatcherQueue().TryEnqueue(Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [this]
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

    void MainWindow::GetPickedActor()
    {
        //Test Code
        for (int i = 0; i < 5; i++)
        {
            hstring componentName = L"TestComponent_" + to_hstring(i);
            //AuthoringTool::ActorComponent component = winrt::make<AuthoringTool::implementation::ActorComponent>(componentName);            
            //SelectedActorViewModel().Components().Append(component);
            //int size = SelectedActorViewModel().Components().Size();
        }

        //renderingEngine_.
    }

    void MainWindow::GetWorldInfo()
    {
        //EngineInterface_WRC::ActorProxy actor(L"firstActor", L"actor");
        //worldViewModel_.ActorInfos().Insert(L"firstActor", actor);
        ////worldViewModel_.ActorInfos().Lookup()
        //worldViewModel_.TestList().Append(actor);
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
        float width = 0.0f;
        float height = 0.0f;
        //Windows::Foundation::Size size = renderingEngine_.GetDefaultBackBufferSize();
        //MainViewModel().BookSku().Title(std::to_wstring(width));
        //myButton().Content(box_value(L"Clicked"));
        //myButton().Content(box_value(std::to_wstring(width)));
        //double test = myButton().XamlRoot().RasterizationScale();
    }

    //void MainWindow::ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args)
    //{
    //    MainViewModel().BookSku().Title(L"To Kill a Mockingbird");
    //}

    //winrt::AuthoringTool::BookstoreViewModel MainWindow::MainViewModel()
    //{
    //    return m_mainViewModel;
    //}
    //AuthoringTool::ActorListViewModel MainWindow::WorldInfoViewModel()
    //{
    //    return worldViewModel_;
    //}


    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        //myButton().Content(box_value(L"Clicked"));
    }
}
