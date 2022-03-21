#pragma once
#include "EngineDX11.g.h"
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"

namespace Level
{
    class World;
}

namespace winrt::DX11Engine_WinUI3_WRC::implementation
{    
    struct EngineDX11 : EngineDX11T<EngineDX11>, public DX::IDeviceNotify
    {
        EngineDX11();
        ~EngineDX11() = default;

        EngineDX11(EngineDX11&&) = default;
        EngineDX11& operator= (EngineDX11&&) = default;

        EngineDX11(EngineDX11 const&) = delete;
        EngineDX11& operator= (EngineDX11 const&) = delete;

        // Initialization and management
        //void EngineDX11::Initialize(winrt::Windows::UI::Core::CoreWindow const& window)
        void Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel);
        void UnInitialize();

        // Basic game loop / Input
        void Tick();
        void StartRenderLoop();
        void StopRenderLoop();
        void ProcessInput();

        // IDeviceNotify
        void OnDeviceLost() override;
        void OnDeviceRestored() override;

        // Messages
        void OnActivated();
        void OnDeactivated();
        void OnSuspending();
        void OnResuming();
        void OnWindowSizeChanged(float width, float height);
        void OnSwapchainXamlChanged(double rasterizationScale, Windows::Foundation::Size size, float compositionScaleX, float compositionScaleY);
        void OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations const& orientation);
        void ValidateDevice();

        //Thread
        winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection GetCriticalSection() { return m_criticalSection; }

        // Properties
        void GetDefaultSize(float& width, float& height) noexcept;

        // private
    private:
        void Update(DX::StepTimer const& timer);
        void Render();

        void Clear();

        bool CreateDeviceDependentResources();
        void CreateWindowSizeDependentResources();

        //// Device resources.
        std::unique_ptr<DX::DeviceResources>    m_deviceResources;

        //// Rendering loop timer.
        DX::StepTimer                           m_timer;

        //ResourceManager         
        //World
        std::unique_ptr<Level::World> m_World;

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


namespace winrt::DX11Engine_WinUI3_WRC::factory_implementation
{
    struct EngineDX11 : EngineDX11T<EngineDX11, implementation::EngineDX11>
    {
    };
}
