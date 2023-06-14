#pragma once
#include "DLLDefine.h"
#define WIN_APPS_SDK

namespace SharedTypes
{
    enum class VirtualKey;
    enum class PointerButton;
}

namespace Engine
{
    namespace Level
    {
        class World;
        class Actor;
    }

	class EngineInterface
	{
    public:
        ENGINE_API EngineInterface() {}
        ENGINE_API ~EngineInterface() = default;
#ifdef WIN_APPS_SDK
        //void Initialize(Microsoft.UI.Xaml.Controls.SwapChainPanel panel);
        ENGINE_API virtual void Initialize(const SwapchainPanelInfo& swapchainPanelInfo_) Pure;
#endif //WIN_APPS_SDK
        ENGINE_API virtual void UnInitialize() Pure;

        // Basic game loop / input        
        ENGINE_API virtual void StartRenderLoop() Pure;
        ENGINE_API virtual void StopRenderLoop() Pure;
         
        ENGINE_API virtual void OnDeviceLost() Pure;
        ENGINE_API virtual void OnDeviceRestored() Pure;

        // Messages
        ENGINE_API virtual void OnActivated() Pure;
        ENGINE_API virtual void OnDeactivated() Pure;
        ENGINE_API virtual void OnSuspending() Pure;
        ENGINE_API virtual void OnResuming() Pure;
        ENGINE_API virtual void OnWindowSizeChanged(SharedTypes::Size windowSize) Pure;
        ENGINE_API virtual void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo) Pure;
        //void OnOrientationChanged(Windows.Graphics.Display.DisplayOrientations orientation);
        ENGINE_API virtual void ValidateDevice() Pure;

        ENGINE_API virtual void KeyProcess(SharedTypes::VirtualKey key, bool isPressed) Pure;
        ENGINE_API virtual void PointerProcess(vector<bool> const& pointerState, float delta, Vector2i pos) Pure;

        // Properties
        ENGINE_API virtual SharedTypes::Size GetDefaultBackBufferSize() Pure;

        //common
        ENGINE_API virtual void LoadScriptProject(std::wstring const& path) Pure;
        ENGINE_API virtual void PickCheck(Vector2i screenPos, shared_ptr<Level::Actor>& pickedActor) Pure;

        //ENGINE_API virtual const unordered_map<const wchar_t*, shared_ptr<Level::Actor>> GetActorList();
	};

	ENGINE_API void InitEngine();
	ENGINE_API void ReleaseEngine();
    ENGINE_API EngineInterface* GetRenderingEngine();
}