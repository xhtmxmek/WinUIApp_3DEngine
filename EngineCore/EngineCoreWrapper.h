#pragma once

//저작도구에서 import되는 엔진코어의 레퍼
#pragma once
#define WIN_APPS_SDK
//#include "Common/StepTimer.h"
#include "DLLDefine.h"

namespace Engine
{
    namespace Type
    {
        struct Size;
    }

    struct SwapchainPanelInfo;
    class EngineCore;

    class EngineCoreWrapper
    {
    public:
        ENGINE_API EngineCoreWrapper();
        ENGINE_API ~EngineCoreWrapper();
#ifdef WIN_APPS_SDK
        //void Initialize(Microsoft.UI.Xaml.Controls.SwapChainPanel panel);
        ENGINE_API void Initialize(const SwapchainPanelInfo& swapChainPanelInfo);
#endif //WIN_APPS_SDK
        ENGINE_API void UnInitialize();

        // Basic game loop / input
        ENGINE_API void Tick();
        ENGINE_API void StartRenderLoop();
        ENGINE_API void StopRenderLoop();
        ENGINE_API void ProcessInput();

        ENGINE_API void OnDeviceLost();
        ENGINE_API void OnDeviceRestored();

        // Messages
        ENGINE_API void OnActivated();
        ENGINE_API void OnDeactivated();
        ENGINE_API void OnSuspending();
        ENGINE_API void OnResuming();
        ENGINE_API void OnWindowSizeChanged(float width, float height);
        //ENGINE_API void OnSwapchainXamlChanged(double rasterizationScale, Type::Size size, float compositonScaleX, float compositonScaleY);
        ENGINE_API void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo);
        //void OnOrientationChanged(Windows.Graphics.Display.DisplayOrientations orientation);
        ENGINE_API void ValidateDevice();

        //Thread
        //winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection GetCriticalSection() { return m_criticalSection; }
        ENGINE_API std::mutex& GetMutex();

        // Properties
        ENGINE_API void GetDefaultSize(float& width, float& height) noexcept;

        //common
        ENGINE_API void LoadScriptProject(std::wstring const& path);

        // private
    private:
        EngineCore* EngineCoreNative;
    };
}