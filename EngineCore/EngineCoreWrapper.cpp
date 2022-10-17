#include "pch.h"
#include "Common/StepTimer.h"
#include "EngineCoreWrapper.h"
#include "EngineCore.h"
#include "Common/DeviceResources.h"

namespace Engine
{
    extern void ExitGame() noexcept;

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

    EngineCoreWrapper::EngineCoreWrapper()
    {
        EngineCoreNative = new EngineCore();
    }

    EngineCoreWrapper::~EngineCoreWrapper()
    {
        delete EngineCoreNative;
    }

    void EngineCoreWrapper::Initialize(const SwapchainPanelInfo& swapChainPanelInfo)
    {
        EngineCoreNative->Initialize(swapChainPanelInfo);
    }

    void EngineCoreWrapper::UnInitialize()
    {        
        DX::DeviceResourcesUtil::GetDeviceResources().reset();
        // m_spriteBatch.reset();
    }
#pragma endregion


#pragma region Frame Update
    // Executes the basic game loop.
    void EngineCoreWrapper::Tick()
    {
        EngineCoreNative->Tick();
    }

    void EngineCoreWrapper::StartRenderLoop()
    {
        EngineCoreNative->StartRenderLoop();
    }

    void EngineCoreWrapper::StopRenderLoop()
    {
        EngineCoreNative->StopRenderLoop();
    }
#pragma endregion


#pragma region Message Handlers
    // Message handlers
    void EngineCoreWrapper::OnActivated()
    {
        EngineCoreNative->OnActivated();
    }

    void EngineCoreWrapper::OnDeactivated()
    {
        EngineCoreNative->OnDeactivated();
    }

    void EngineCoreWrapper::OnSuspending()
    {
        EngineCoreNative->OnSuspending();
    }

    void EngineCoreWrapper::OnResuming()
    {
        EngineCoreNative->OnResuming();        
    }

    void EngineCoreWrapper::OnWindowSizeChanged(float width, float height)
    {
        EngineCoreNative->OnWindowSizeChanged(width, height);
    }

    void EngineCoreWrapper::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo)
    {
        EngineCoreNative->OnSwapchainXamlChanged(swapChainPanelInfo);
    }

    //void EngineCore::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
    //{
    //    DX::DeviceResourcesUtil::GetDeviceResources()->SetCurrentOrientation(orientation);
    //    CreateWindowSizeDependentResources();
    //}


    std::mutex& EngineCoreWrapper::GetMutex()
    {
        return EngineCoreNative->GetMutex();
    }

    void EngineCoreWrapper::ValidateDevice()
    {
        DX::DeviceResourcesUtil::GetDeviceResources()->ValidateDevice();
    }

    // Properties
    void EngineCoreWrapper::GetDefaultSize(float& width, float& height) noexcept //const noexcept
    {
        EngineCoreNative->GetDefaultSize(width, height);
    }
    void EngineCoreWrapper::LoadScriptProject(wstring const& path)
    {
        EngineCoreNative->LoadScriptProject(path);
    }

#pragma endregion

}