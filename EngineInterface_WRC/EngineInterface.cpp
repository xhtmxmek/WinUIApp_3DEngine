#include "pch.h"
#include "EngineInterface.h"
#if __has_include("EngineInterface.g.cpp")
#include "EngineInterface.g.cpp"
#endif

#include "../EngineCore/EngineCore.h" //
#include "../EngineCore/Common/EngineHelper.h"

extern void ExitGame() noexcept;

//using namespace winrt;
using namespace winrt::Windows::System::Threading;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

namespace winrt::EngineInterface_WRC::implementation
{
	EngineInterface::EngineInterface()
	{		
		engineCoreNative_ = make_unique<Engine::EngineCore>();
	}

#pragma region Initialize
	void EngineInterface::Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
	{
		InitializeSwapChainPanelInfo(panel);
		engineCoreNative_->Initialize(SwapchainPanelInfo);
	}

	void EngineInterface::UnInitialize()
	{
		engineCoreNative_->UnInitialize();
	}

	void EngineInterface::InitializeSwapChainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{
		SwapchainPanelUI = panel;		
		SetSwapchainPanelInfo(panel);		
	}

	void EngineInterface::SetSwapchainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{
		
		SwapchainPanelInfo.ActureSize = SharedTypes::Size(panel.ActualSize().x, panel.ActualSize().y);
		SwapchainPanelInfo.CompositionScale = Vector2f(panel.CompositionScaleX(), panel.CompositionScaleY());
		SwapchainPanelInfo.IsLoaded = panel.IsLoaded();
		SwapchainPanelInfo.RasterizationScale = panel.RasterizationScale();

		SwapchainPanelInfo.RegisterSwapChainToUIPanel = [&](IDXGISwapChain3* engineSwapChain) {

			EngineSwapChain = engineSwapChain;

			SwapchainPanelUI.DispatcherQueue().TryEnqueue(winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [&]
				{
					auto panelNative = SwapchainPanelUI.as<ISwapChainPanelNative>();
					panelNative->SetSwapChain(EngineSwapChain);					
				});
		};
	}
	void EngineInterface::SetRegisterSwapChainFunc(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{			
	}
#pragma endregion


#pragma region Frame Update
	// Executes the basic game loop.
	void EngineInterface::StartRenderLoop()
	{
		engineCoreNative_->StartRenderLoop();
	}

	void EngineInterface::StopRenderLoop()
	{      
		engineCoreNative_->StopRenderLoop();
	}
#pragma endregion

#pragma region Message Handlers
	// Message handlers
	void EngineInterface::OnActivated()
	{
		engineCoreNative_->OnActivated();
	}

	void EngineInterface::OnDeactivated()
	{
		engineCoreNative_->OnDeactivated();
	}

	void EngineInterface::OnSuspending()
	{
		engineCoreNative_->OnSuspending();
	}

	void EngineInterface::OnResuming()
	{
		engineCoreNative_->OnResuming();
	}

	void EngineInterface::OnWindowSizeChanged(Windows::Foundation::Size windowSize)
	{
		engineCoreNative_->OnWindowSizeChanged(SharedTypes::Size(windowSize.Width, windowSize.Height));
	}

	void EngineInterface::OnSwapchainXamlChanged(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{		
		SetSwapchainPanelInfo(panel);
		engineCoreNative_->OnSwapchainXamlChanged(SwapchainPanelInfo);
	}

	void EngineInterface::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
	{
		//engineCoreNative_->O
	}

	void EngineInterface::KeyboardProcess(winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
	{					
		SharedTypes::VirtualKey nativekey = static_cast<SharedTypes::VirtualKey>(args.Key());
		engineCoreNative_->KeyProcess(nativekey, !args.KeyStatus().IsKeyReleased);
	}

	void EngineInterface::StartTracking(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{
		SharedTypes::PointerButton button;
		if (args.CurrentPoint().Properties().IsLeftButtonPressed())
			button = SharedTypes::PointerButton::LeftButton;
		else if (args.CurrentPoint().Properties().IsRightButtonPressed())
			button = SharedTypes::PointerButton::RightButton;		
	}

	void EngineInterface::TrackingUpdate(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{
		args.CurrentPoint().Position();
	}

	winrt::EngineInterface_WRC::PointerActionResult EngineInterface::StopTracking(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{
		SharedTypes::PointerButton button;
		if (args.CurrentPoint().Properties().IsLeftButtonPressed())
			button = SharedTypes::PointerButton::LeftButton;
		else if (args.CurrentPoint().Properties().IsRightButtonPressed())
			button = SharedTypes::PointerButton::RightButton;

		PointerActionResult result;
						
		//engineCoreNative_->PointerProcess()

		return result;
	}

	void EngineInterface::PointerWheelChanged(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{
		//winrt::Windows::Foundation::Numerics::float2			
		if (args.CurrentPoint().Properties().IsHorizontalMouseWheel())			
			args.CurrentPoint().Properties().MouseWheelDelta();
	}

	// Properties
	Windows::Foundation::Size EngineInterface::GetDefaultBackBufferSize() noexcept //const noexcept
	{
		//Engine::Type::Size size = engineCoreNative_->GetDefaultBackBufferSize();
		//return Size(size.Width, size.Height);
		return Windows::Foundation::Size(0, 0);
	}
	void EngineInterface::LoadScriptProject(hstring const& path)
	{
		engineCoreNative_->LoadScriptProject(path.c_str());
	}

#pragma endregion

}
