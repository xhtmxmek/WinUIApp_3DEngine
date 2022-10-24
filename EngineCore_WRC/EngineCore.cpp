#include "pch.h"
#include "EngineCore.h"
#if __has_include("EngineCore.g.cpp")
#include "EngineCore.g.cpp"
#endif

#include "../EngineCore/EngineCore.h" //
#include "../EngineCore/Common/EngineHelper.h"

extern void ExitGame() noexcept;

//using namespace winrt;
using namespace winrt::Windows::System::Threading;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

namespace winrt::EngineCore_WRC::implementation
{
	EngineCore::EngineCore()
	{		
		EngineCoreNative = make_unique<Engine::EngineCore>();
	}

#pragma region Initialize
	void EngineCore::Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
	{
		InitializeSwapChainPanelInfo(panel);
		EngineCoreNative->Initialize(SwapchainPanelInfo);
	}

	void EngineCore::UnInitialize()
	{
		EngineCoreNative->UnInitialize();
	}

	void EngineCore::InitializeSwapChainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{
		SwapchainPanelUI = panel;		
		SetSwapchainPanelInfo(panel);		
	}

	void EngineCore::SetSwapchainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
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
	void EngineCore::SetRegisterSwapChainFunc(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{			
	}
#pragma endregion


#pragma region Frame Update
	// Executes the basic game loop.
	void EngineCore::StartRenderLoop()
	{
		EngineCoreNative->StartRenderLoop();
	}

	void EngineCore::StopRenderLoop()
	{      
		EngineCoreNative->StopRenderLoop();
	}
#pragma endregion

#pragma region Message Handlers
	// Message handlers
	void EngineCore::OnActivated()
	{
		EngineCoreNative->OnActivated();
	}

	void EngineCore::OnDeactivated()
	{
		EngineCoreNative->OnDeactivated();
	}

	void EngineCore::OnSuspending()
	{
		EngineCoreNative->OnSuspending();
	}

	void EngineCore::OnResuming()
	{
		EngineCoreNative->OnResuming();
	}

	void EngineCore::OnWindowSizeChanged(float width, float height)
	{
		EngineCoreNative->OnWindowSizeChanged(width, height);
	}

	void EngineCore::OnSwapchainXamlChanged(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{		
		SetSwapchainPanelInfo(panel);
		EngineCoreNative->OnSwapchainXamlChanged(SwapchainPanelInfo);
	}

	void EngineCore::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
	{
		//EngineCoreNative->O
	}

	// Properties
	Windows::Foundation::Size EngineCore::GetDefaultBackBufferSize() noexcept //const noexcept
	{
		//Engine::Type::Size size = EngineCoreNative->GetDefaultBackBufferSize();
		//return Size(size.Width, size.Height);
		return Windows::Foundation::Size(0, 0);
	}
	void EngineCore::LoadScriptProject(hstring const& path)
	{
		EngineCoreNative->LoadScriptProject(path.c_str());
	}

#pragma endregion

}
