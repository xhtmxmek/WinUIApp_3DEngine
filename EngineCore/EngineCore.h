#pragma once
#define WIN_APPS_SDK
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"

namespace Engine
{    
    struct SwapchainPanelInfo
    {

    };
    class EngineCore
    {
#ifdef WIN_APPS_SDK
        //void Initialize(Microsoft.UI.Xaml.Controls.SwapChainPanel panel);
        void Initialize(const SwapchainPanelInfo& swapChainPanelInfo);
#endif //WIN_APPS_SDK
        void UnInitialize();

        // Basic game loop / input
        void Tick();
        void StartRenderLoop();
        void StopRenderLoop();
        void ProcessInput();
        
        // Messages
        void OnActivated();
        void OnDeactivated();
        void OnSuspending();
        void OnResuming();
        void OnWindowSizeChanged(float width, float height);
        //void OnSwapchainXamlChanged(double rasterizationScale, Windows.Foundation.Size size, float compositonScaleX, float compositonScaleY);
        //void OnOrientationChanged(Windows.Graphics.Display.DisplayOrientations orientation);
        void ValidateDevice();

        //Thread
        winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection GetCriticalSection() { return m_criticalSection; }

        // Properties
        void GetDefaultSize(float& width, float& height) noexcept;

        //common
        void LoadScriptProject(hstring const& path);

        // private
    private:
        void Update(DX::StepTimer const& timer);
        void Render();

        void Clear();

        bool CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();

        //// Device resources.
        //std::unique_ptr<DX::DeviceResources>    m_deviceResources;

        //// Rendering loop timer.
        DX::StepTimer                           m_timer;

        //ResourceManager         
        //World
        shared_ptr<Engine::Level::World> m_World;

        //texture
        com_ptr<ID3D11ShaderResourceView> m_texture;

        ////sprite
        std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
        DirectX::SimpleMath::Vector2 m_screenPos;
        DirectX::SimpleMath::Vector2 m_origin;

        //Thread 관련
        Windows::Foundation::IAsyncAction m_renderLoopWorker;
        winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection m_criticalSection{ nullptr };
        // 현재 입력 포인터 위치를 추적합니다.
        float m_pointerLocationX;
    };
}