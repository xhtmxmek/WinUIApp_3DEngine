#pragma once
#define WIN_APPS_SDK
//#include "Common/StepTimer.h"
#include "DLLDefine.h"

/*
EngineCore는 최대한 플랫폼 독립적인 코드로 가는것이 목표
렌더링에 관련된 API는 사용하지만, 운영체제 관련된 코드는 최대한 배제할 예정
운영체제 관련된 코드(Ex window: winrt)는 엔진 인터페이스쪽에서 처리하는게 맞는거 같음.
*/

namespace Engine
{    
    namespace DX
    {
        class StepTimer;
    }

    namespace Level
    {
        class World;
    }

    namespace Type
    {
        struct Size;
    }            
    class EngineCore
    {
    public:
        ENGINE_API EngineCore():RenderLoopActivate(false), ProjectHandle(nullptr) {}
        ENGINE_API ~EngineCore() = default;
#ifdef WIN_APPS_SDK
        //void Initialize(Microsoft.UI.Xaml.Controls.SwapChainPanel panel);
        ENGINE_API void Initialize(const SwapchainPanelInfo& swapChainPanelInfo);
#endif //WIN_APPS_SDK
        ENGINE_API void UnInitialize();

        // Basic game loop / input        
        ENGINE_API void StartRenderLoop();
        ENGINE_API void StopRenderLoop();
        
        ENGINE_API void OnDeviceLost();
        ENGINE_API void OnDeviceRestored();

        // Messages
        ENGINE_API void OnActivated();
        ENGINE_API void OnDeactivated();
        ENGINE_API void OnSuspending();
        ENGINE_API void OnResuming();
        ENGINE_API void OnWindowSizeChanged(SharedTypes::Size windowSize);
        ENGINE_API void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo);
        //void OnOrientationChanged(Windows.Graphics.Display.DisplayOrientations orientation);
        ENGINE_API void ValidateDevice();

        //Thread
        //winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection GetCriticalSection() { return m_criticalSection; }
        //std::mutex& GetMutex() { return EngineTickMutex; }

        // Properties
        ENGINE_API Size GetDefaultBackBufferSize() noexcept
        {
            return Size(800.0f, 600.0f);
        }

        //common
        ENGINE_API void LoadScriptProject(std::wstring const& path);

        // private
    private:
        void Tick();
        void Update(const std::unique_ptr<Engine::DX::StepTimer>& timer);
        void Render();

        void ProcessInput();

        void Clear();

        void InitializeGlobalObjects();
        void LoadDefaultProject();
        bool CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();

        //// Device resources.
        //std::unique_ptr<DX::DeviceResources>    m_deviceResources;

        //// Rendering loop timer.
        std::unique_ptr<Engine::DX::StepTimer> Timer;
        std::shared_ptr<Engine::Level::World> m_World;
        //std::unique_ptr<DirectX::Keyboard> m_keyboard;
        //std::unique_ptr<DirectX::Mouse> m_mouse;


        //Thread 관련    
        bool RenderLoopActivate;
        std::thread RenderLoopThread;
        std::mutex EngineTickMutex;
        //Windows::Foundation::IAsyncAction m_renderLoopWorker;
        //winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection m_criticalSection{ nullptr };
        // 현재 입력 포인터 위치를 추적합니다.
        float m_pointerLocationX;

        HMODULE ProjectHandle;
    };
}