#pragma once
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
	namespace World
	{
		class WorldObject;
		class Actor;
	}

	namespace Renderer
	{
		class RenderThread;
	}

	class EngineCore
	{
	public:
		ENGINE_API EngineCore() : ProjectHandle(nullptr) {}
		ENGINE_API ~EngineCore() = default;

#pragma region Initialize
#ifdef WIN_APPS_SDK
	public:
		ENGINE_API void Initialize(const SwapchainPanelInfo& swapchainPanelInfo_);
	private:
		void InitializeCoreThread(const SwapchainPanelInfo& swapchainPanelInfo_);
#endif //WIN_APPS_SDK
#pragma endregion

#pragma region Uninitialize
	public:
		ENGINE_API void UnInitialize();
#pragma endregion        

#pragma region Windows Dedicated
	public:
		ENGINE_API IDXGISwapChain3* GetSwapChain();
#pragma endregion

#pragma region Active Control
		ENGINE_API void Run();
		ENGINE_API void Stop();
#pragma endregion

#pragma region Window Message Handlers
	public:
		ENGINE_API void OnActivated();
		ENGINE_API void OnDeactivated();
		ENGINE_API void OnSuspending();
		ENGINE_API void OnResuming();
		ENGINE_API void OnWindowSizeChanged(SharedTypes::Size windowSize);
		ENGINE_API void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo);

		ENGINE_API void KeyProcess(SharedTypes::VirtualKey key, bool isPressed);
		ENGINE_API void PointerProcess(vector<bool> const& pointerState);
		ENGINE_API void PointerProcess(Vector2i pos);
		ENGINE_API void PointerProcess(int wheelDelta);

		ENGINE_API void PickCheck(Vector2i screenPos, shared_ptr<World::Actor>& pickedActor);
		ENGINE_API weak_ptr<World::Actor> GetActor(int index);
		ENGINE_API weak_ptr<World::Actor> GetActor(const string& name);
		ENGINE_API size_t GetNumActoRHIst();
#pragma endregion

#pragma region ProjectLoad
	public:
		ENGINE_API void LoadScriptProject(std::wstring const& path);
		HMODULE ProjectHandle;
#pragma endregion

#pragma region WorkerThread
	private:
		unique_ptr<GameThread> gameThread;
		unique_ptr<Renderer::RenderThread> renderThread;
#pragma endregion
	};

	ENGINE_API void InitEngine();
	ENGINE_API void ReleaseEngine();
	ENGINE_API EngineCore* GetRenderingEngine();
}