#pragma once
#define WIN_APPS_SDK
//#include "Common/StepTimer.h"
#include "DLLDefine.h"

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
        ENGINE_API EngineCore():RenderLoopActivate(false){}
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
        ENGINE_API void OnWindowSizeChanged(float width, float height);
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

        bool CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();

        //// Device resources.
        //std::unique_ptr<DX::DeviceResources>    m_deviceResources;

        //// Rendering loop timer.
        std::unique_ptr<Engine::DX::StepTimer> Timer;
        //Engine::DX::StepTimer* Timer;
        //ResourceManager         
        //World
        std::shared_ptr<Engine::Level::World> m_World;

        //texture
        //wil::com_ptr<ID3D11ShaderResourceView> m_texture;

        ////sprite
        //std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
        //DirectX::SimpleMath::Vector2 m_screenPos;
        //DirectX::SimpleMath::Vector2 m_origin;

        //Thread 관련    
        bool RenderLoopActivate;
        std::thread RenderLoopThread;
        std::mutex EngineTickMutex;
        //Windows::Foundation::IAsyncAction m_renderLoopWorker;
        //winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection m_criticalSection{ nullptr };
        // 현재 입력 포인터 위치를 추적합니다.
        float m_pointerLocationX;
    };
}