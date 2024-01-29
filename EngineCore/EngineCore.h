#pragma once
#define WIN_APPS_SDK
//#include "Common/StepTimer.h"
#include "DLLDefine.h"

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

    class EngineCore
    {
    public:
        ENGINE_API EngineCore():RenderLoopActivate(false), ProjectHandle(nullptr) {}
        ENGINE_API ~EngineCore() = default;
#ifdef WIN_APPS_SDK
        //void Initialize(Microsoft.UI.Xaml.Controls.SwapChainPanel panel);
        ENGINE_API void Initialize(const SwapchainPanelInfo& swapchainPanelInfo_);
#endif //WIN_APPS_SDK
        ENGINE_API void UnInitialize();
        ENGINE_API IDXGISwapChain3* GetSwapChain();


        // Basic game loop / inputs        
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
        ENGINE_API void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo);
        //void OnOrientationChanged(Windows.Graphics.Display.DisplayOrientations orientation);
        ENGINE_API void ValidateDevice();

        ENGINE_API void KeyProcess(SharedTypes::VirtualKey key, bool isPressed);
        ENGINE_API void PointerProcess(vector<bool> const& pointerState);
        ENGINE_API void PointerProcess(Vector2i pos);
        ENGINE_API void PointerProcess(int wheelDelta);

        // Properties
        ENGINE_API SharedTypes::Size GetDefaultBackBufferSize() noexcept
        {
            return SharedTypes::Size(800.0f, 600.0f);
        }

        //common
        ENGINE_API void LoadScriptProject(std::wstring const& path);
        ENGINE_API void PickCheck(Vector2i screenPos, shared_ptr<Level::Actor>& pickedActor);

        ENGINE_API weak_ptr<Level::Actor> GetActor(int index);
        ENGINE_API weak_ptr<Level::Actor> GetActor(const string& name);
        ENGINE_API size_t GetNumActorList();

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
        
    private:
        std::shared_ptr<Engine::DX::StepTimer> Timer;
        std::shared_ptr<Engine::Level::World> m_World;
        
        bool RenderLoopActivate;
        std::thread RenderLoopThread;
        std::mutex EngineTickMutex;
        //Windows::Foundation::IAsyncAction m_renderLoopWorker;
        //IRenderer*를 통해서 Render. Mobile용과 DeferredRenderer가 따로 있음
        //World가 Level을 물고 있는 것이다. World는 하나의 가상 세계이고 Level은 가상세계에 존재하는 장소(구역이다.)World는 Map안에 들어있다.



        HMODULE ProjectHandle;
    };

    ENGINE_API void InitEngine();
    ENGINE_API void ReleaseEngine();
    ENGINE_API EngineCore* GetRenderingEngine();
}