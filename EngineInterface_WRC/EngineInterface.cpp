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
		EngineCoreNative = make_unique<Engine::EngineCore>();
	}

#pragma region Initialize
	void EngineInterface::Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
	{
		InitializeSwapChainPanelInfo(panel);
		EngineCoreNative->Initialize(SwapchainPanelInfo);
	}

	void EngineInterface::UnInitialize()
	{
		EngineCoreNative->UnInitialize();
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
		EngineCoreNative->StartRenderLoop();
	}

	void EngineInterface::StopRenderLoop()
	{      
		EngineCoreNative->StopRenderLoop();
	}
#pragma endregion

#pragma region Message Handlers
	// Message handlers
	void EngineInterface::OnActivated()
	{
		EngineCoreNative->OnActivated();
	}

	void EngineInterface::OnDeactivated()
	{
		EngineCoreNative->OnDeactivated();
	}

	void EngineInterface::OnSuspending()
	{
		EngineCoreNative->OnSuspending();
	}

	void EngineInterface::OnResuming()
	{
		EngineCoreNative->OnResuming();
	}

	void EngineInterface::OnWindowSizeChanged(float width, float height)
	{
		EngineCoreNative->OnWindowSizeChanged(width, height);
	}

	void EngineInterface::OnSwapchainXamlChanged(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{		
		SetSwapchainPanelInfo(panel);
		EngineCoreNative->OnSwapchainXamlChanged(SwapchainPanelInfo);
	}

	void EngineInterface::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
	{
		//EngineCoreNative->O
	}

	// Properties
	Windows::Foundation::Size EngineInterface::GetDefaultBackBufferSize() noexcept //const noexcept
	{
		//Engine::Type::Size size = EngineCoreNative->GetDefaultBackBufferSize();
		//return Size(size.Width, size.Height);
		return Windows::Foundation::Size(0, 0);
	}
	void EngineInterface::LoadScriptProject(hstring const& path)
	{
		EngineCoreNative->LoadScriptProject(path.c_str());
	}

#pragma endregion

}
