#include "pch.h"
#include "EngineCore.h"
#if __has_include("EngineCore.g.cpp")
#include "EngineCore.g.cpp"
#endif
//#include "Common/EngineHelper.h"
//#include "Common/EngineCriticalSection.h"
//#include "Common/Engine_Scoped_Lock.h"
//#include "Level/Level.h"
//#include "Level/World.h"
//#include "Renderer/LevelRenderer.h"
//#include "Level/Actor/ActorManager/ActorManager.h"
//#include "EngineAsset/Texture.h"
//#include <fstream>
//#include <sstream>
//#include "Common/RuntimeContext.h"
#include "../EngineCore/EngineCore.h" //

extern void ExitGame() noexcept;

//using namespace winrt;
using namespace winrt::Windows::System::Threading;
//using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

namespace winrt::EngineCore_WRC::implementation
{
    EngineCore::EngineCore()        
    {                
        //DX::DeviceResourcesUtil::GetDeviceResources() = std::make_unique<DX::DeviceResources>();
        EngineCoreNative = make_unique<Engine::EngineCore>();
    }

#pragma region Initialize
    //void EngineCore::Initialize(HWND window)
    //{
    //    CreateDeviceDependentResources();
    //    DX::DeviceResourcesUtil::GetDeviceResources()->SetWindow(window, 500, 500);
    //    CreateWindowSizeDependentResources();

    //    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    //    // e.g. for 60 FPS fixed timestep update logic, call:
    //    /*
    //    m_timer.SetFixedTimeStep(true);
    //    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    //    */
    //}

    void EngineCore::Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
    {
        //EngineCoreNative->Initialize(panel);
    }

    void EngineCore::UnInitialize()
    {
        EngineCoreNative->UnInitialize();
    }
#pragma endregion


#pragma region Frame Update
    // Executes the basic game loop.
    void EngineCore::Tick()
    {
        //EngineCorenative->
    }

    void EngineCore::StartRenderLoop()
    {
        ProcessInput();
        
        //if (m_renderLoopWorker != nullptr && m_renderLoopWorker.Status() == winrt::Windows::Foundation::AsyncStatus::Started)        
        //    return;        
        //
        //auto workItemHandler = WorkItemHandler([this, strong_this{ get_strong() }](winrt::Windows::Foundation::IAsyncAction action)
        //    {                
        //        while (action.Status() == winrt::Windows::Foundation::AsyncStatus::Started)
        //        {                                        
        //            winrt::DX11Engine_WinUI3_WRC::Engine_Scoped_Lock lock{ m_criticalSection };                    
        //            Tick();
        //        }
        //    });

        //// 전용인 우선 순위가 높은 백그라운드 스레드에서 작업을 실행합니다.
        //m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
    }

    void EngineCore::StopRenderLoop()
    {        
        //DX::DeviceResourcesUtil::GetDeviceResources()->Trim();
        //m_renderLoopWorker.Cancel();                
    }
#pragma endregion


    // 게임 상태를 업데이트하기 전에 사용자의 모든 입력 처리
    void EngineCore::ProcessInput()
    {
        // TODO: 여기에 프레임 입력 처리별로 추가합니다.
        //m_sceneRenderer->TrackingUpdate(m_pointerLocationX);
    }

#pragma region Message Handlers
    // Message handlers
    void EngineCore::OnActivated()
    {
        // TODO: Game is becoming active window.
    }

    void EngineCore::OnDeactivated()
    {
        // TODO: Game is becoming background window.
    }

    void EngineCore::OnSuspending()
    {
        EngineCoreNative->OnSuspending();
        // TODO: Game is being power-suspended.
    }

    void EngineCore::OnResuming()
    {
        EngineCoreNative->OnResuming();

        // TODO: Game is being power-resumed.
    }

    void EngineCore::OnWindowSizeChanged(float width, float height)
    {
        EngineCoreNative->OnWindowSizeChanged(width, height);
    }

    void EngineCore::OnSwapchainXamlChanged(double rasterizationScale, winrt::Windows::Foundation::Size const& size, float compositonScaleX, float compositonScaleY)
    {
        //EngineCoreNative->OnSwapchainXamlChanged();
    }

    void EngineCore::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
    {
        //EngineCoreNative->O
    }

    void EngineCore::ValidateDevice()
    {
        //DX::DeviceResourcesUtil::GetDeviceResources()->ValidateDevice();
    }

    // Properties
    void EngineCore::GetDefaultSize(float& width, float& height) noexcept //const noexcept
    {
        EngineCoreNative->GetDefaultSize(width, height);
    }
    void EngineCore::LoadScriptProject(hstring const& path)
    {
        EngineCoreNative->LoadScriptProject(path.c_str());
    }

#pragma endregion

}
