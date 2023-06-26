#pragma once
#define WIN_APPS_SDK
//#include "Common/StepTimer.h"
#include "DLLDefine.h"
#include "EngineInterface.h"
/*
EngineCore는 최대한 플랫폼 독립적인 코드로 가는것이 목표
렌더링에 관련된 API는 사용하지만, 운영체제 관련된 코드는 최대한 배제할 예정
운영체제 관련된 코드(Ex window: winrt)는 엔진 인터페이스쪽에서 처리하는게 맞는거 같음.
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
        class Actor;
    }

    class EngineCore : public EngineInterface     
    {
    public:
        EngineCore():RenderLoopActivate(false), ProjectHandle(nullptr) {}
        ~EngineCore() = default;
#ifdef WIN_APPS_SDK
        //void Initialize(Microsoft.UI.Xaml.Controls.SwapChainPanel panel);
        void Initialize(const SwapchainPanelInfo& swapchainPanelInfo_) override;
#endif //WIN_APPS_SDK
        void UnInitialize() override;

        // Basic game loop / inputs        
        void StartRenderLoop() override;
        void StopRenderLoop() override;
        
        void OnDeviceLost() override;
        void OnDeviceRestored() override;

        // Messages
        void OnActivated() override;
        void OnDeactivated() override;
        void OnSuspending() override;
        void OnResuming() override;
        void OnWindowSizeChanged(SharedTypes::Size windowSize) override;
        void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo) override;
        //void OnOrientationChanged(Windows.Graphics.Display.DisplayOrientations orientation);
        void ValidateDevice() override;

        void KeyProcess(SharedTypes::VirtualKey key, bool isPressed) override;
        void PointerProcess(vector<bool> const& pointerState, float delta, Vector2i pos) override;

        // Properties
        SharedTypes::Size GetDefaultBackBufferSize() noexcept override
        {
            return SharedTypes::Size(800.0f, 600.0f);
        }

        //common
        void LoadScriptProject(std::wstring const& path) override;
        void PickCheck(Vector2i screenPos, shared_ptr<Level::Actor>& pickedActor) override;

        const unordered_map<const wchar_t*, shared_ptr<Level::Actor>> GetActorList();

        // private
    private:
        void Tick();
        void Update();
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