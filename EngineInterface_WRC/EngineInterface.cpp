﻿#include "pch.h"
#include "EngineInterface.h"
#if __has_include("EngineInterface.g.cpp")
#include "EngineInterface.g.cpp"
#endif

#include "EngineCore.h"
#include "Common/EngineHelper.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"

extern void ExitGame() noexcept;

//using namespace winrt;
using namespace winrt::Windows::System::Threading;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

namespace winrt::EngineInterface_WRC::implementation
{
	EngineInterface::EngineInterface()
		:engineSwapChain_(nullptr),
		//pickedActor_(nullptr),
		pickedPos_(0.0f, 0.0f)
	{
		engineCoreNative_ = make_unique<Engine::EngineCore>();
	}

#pragma region Initialize
	void EngineInterface::Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
	{
		InitializeSwapChainPanelInfo(panel);
		engineCoreNative_->Initialize(swapchainPanelInfo_);

		UINT buttonCount = static_cast<int>(SharedTypes::PointerButton::Button_Max);
		MouseButtonState.reserve(buttonCount);
		MouseButtonState.resize(buttonCount);
	}

	void EngineInterface::UnInitialize()
	{
		engineCoreNative_->UnInitialize();
	}

	void EngineInterface::InitializeSwapChainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{
		swapchainPanelUI_ = panel;
		SetSwapchainPanelInfo(panel);
	}

	void EngineInterface::SetSwapchainPanelInfo(const Microsoft::UI::Xaml::Controls::SwapChainPanel& panel)
	{

		swapchainPanelInfo_.ActureSize = SharedTypes::Size(panel.ActualSize().x, panel.ActualSize().y);
		swapchainPanelInfo_.CompositionScale = Vector2f(panel.CompositionScaleX(), panel.CompositionScaleY());
		swapchainPanelInfo_.IsLoaded = panel.IsLoaded();
		swapchainPanelInfo_.RasterizationScale = panel.RasterizationScale();

		swapchainPanelInfo_.RegisterSwapChainToUIPanel = [&](IDXGISwapChain3* engineSwapChain) {

			engineSwapChain_ = engineSwapChain;

			swapchainPanelUI_.DispatcherQueue().TryEnqueue(winrt::Microsoft::UI::Dispatching::DispatcherQueuePriority::High, [&]
				{
					auto panelNative = swapchainPanelUI_.as<ISwapChainPanelNative>();
					panelNative->SetSwapChain(engineSwapChain_);
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
		engineCoreNative_->OnSwapchainXamlChanged(swapchainPanelInfo_);
	}

	void EngineInterface::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
	{
	}

	void EngineInterface::KeyboardProcess(winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& args)
	{
		SharedTypes::VirtualKey nativekey = static_cast<SharedTypes::VirtualKey>(args.Key());
		engineCoreNative_->KeyProcess(nativekey, !args.KeyStatus().IsKeyReleased);
	}

	void EngineInterface::StartTracking(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{
		CheckButtonState(args);
		engineCoreNative_->PointerProcess(MouseButtonState, 0.0f, Vector2i((int)args.CurrentPoint().Position().X, (int)args.CurrentPoint().Position().Y));
		//engineCoreNative_->PickCheck(Vector2i(0, 0), pickedActor_);
	}

	void EngineInterface::TrackingUpdate(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{		
		CheckButtonState(args);
		engineCoreNative_->PointerProcess(MouseButtonState, 0.0f, Vector2i((int)args.CurrentPoint().Position().X, (int)args.CurrentPoint().Position().Y));
	}

	//winrt::EngineInterface_WRC::PointerActionResult EngineInterface::StopTracking(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	//{
	//	CheckButtonState(args);		
	//	engineCoreNative_->PointerProcess(MouseButtonState, 0.0f, Vector2i((int)args.CurrentPoint().Position().X, (int)args.CurrentPoint().Position().Y));

	//	Vector2f currentPos = Vector2f(args.CurrentPoint().Position().X, args.CurrentPoint().Position().Y);
	//	if (currentPos == pickedPos_)
	//	{			
	//	}
	//	PointerActionResult result;
	//	return result;
	//}

	void EngineInterface::PointerWheelChanged(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{
		//winrt::Windows::Foundation::Numerics::float2			
		if (args.CurrentPoint().Properties().IsHorizontalMouseWheel())
			args.CurrentPoint().Properties().MouseWheelDelta();
	}

	void EngineInterface::CheckButtonState(winrt::Microsoft::UI::Input::PointerEventArgs const& args)
	{		
		MouseButtonState[static_cast<UINT>(SharedTypes::PointerButton::LeftButton)] = args.CurrentPoint().Properties().IsLeftButtonPressed();
		MouseButtonState[static_cast<UINT>(SharedTypes::PointerButton::RightButton)] = args.CurrentPoint().Properties().IsRightButtonPressed();
	}

	void EngineInterface::UpdateActorProxy()
	{

		//actorProxy_.Components().Clear();
		//for (auto iterComponent : pickedActor_->Components())
		//{								
		//	wstring convertName;			
		//	convertName.assign(iterComponent.second->Name().begin(), iterComponent.second->Name().end());

		//	ActorComponentProxy componentProxy(convertName);
		//	for (auto iterProperty : iterComponent.second->Properties())
		//	{
		//		wstring propertyName;
		//		propertyName.assign(iterProperty->Name().begin(), iterProperty->Name().end());
		//		ComponentPropertyProxy propertyProxy(propertyName);
		//		componentProxy.Properties().Append(propertyProxy);					
		//	}
		//	actorProxy_.Components().Append(componentProxy);
		//}
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


	winrt::Windows::Foundation::Collections::IMap<hstring, winrt::EngineInterface_WRC::ActorProxy> EngineInterface::WorldActorList()
	{
		engineCoreNative_->GetActorList();
		//auto coll2{ winrt::single_threaded_map<winrt::hstring, int>(std::move(values)) };
	}
}
