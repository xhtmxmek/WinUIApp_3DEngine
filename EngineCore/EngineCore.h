#pragma once
#include "DLLDefine.h"

/*
* 
EngineCore's goal is to make the code as platform-independent as possible.
APIs related to rendering will be used, but operating system-related code((Ex window: winrt) will be excluded as much as possible.
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
		template<typename AppWindowType>
		ENGINE_API void Initialize(const WindowInitParam<AppWindowType>& initParam)
		{
			Initialize_Inner();
			InitializeCoreThread(initParam);	
			PostInitialize();
		}
	private:
		void Initialize_Inner();		
		void InitializeCoreThread();

		template<typename AppWindowType>
		void PostInitialize(const WindowInitParam<AppWindowType>& initParam)
		{
			renderThread->PostInitialize(initParam);
		}		
#endif //WIN_APPS_SDK
#pragma endregion

#pragma region Uninitialize
	public:
		ENGINE_API void UnInitialize();
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
		ENGINE_API void OnWindowTransformChanged(const WindowParam& WindowParam);		

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