#pragma once
#define WIN_APPS_SDK
//#include "Common/StepTimer.h"
#include "DLLDefine.h"

/*
EngineCore�� �ִ��� �÷��� �������� �ڵ�� ���°��� ��ǥ
�������� ���õ� API�� ���������, �ü�� ���õ� �ڵ�� �ִ��� ������ ����
�ü�� ���õ� �ڵ�(Ex window: winrt)�� ���� �������̽��ʿ��� ó���ϴ°� �´°� ����.
*/

namespace SharedTypes
{
    enum class VirtualKey;
    enum class PointerButton;
}

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

        ENGINE_API void KeyProcess(SharedTypes::VirtualKey key, bool isPressed);
        ENGINE_API void PointerProcess(SharedTypes::PointerButton button, bool isPressed, float delta, Vector2i pos);

        // Properties
        ENGINE_API SharedTypes::Size GetDefaultBackBufferSize() noexcept
        {
            return SharedTypes::Size(800.0f, 600.0f);
        }

        //common
        ENGINE_API void LoadScriptProject(std::wstring const& path);
        ENGINE_API void PickCheck(Vector2i screenPos, shared_ptr<Level::Actor>& pickedActor);

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
        
        std::unique_ptr<Engine::DX::StepTimer> Timer;
        std::shared_ptr<Engine::Level::World> m_World;
        
        bool RenderLoopActivate;
        std::thread RenderLoopThread;
        std::mutex EngineTickMutex;
        //Windows::Foundation::IAsyncAction m_renderLoopWorker;



        HMODULE ProjectHandle;
    };
}