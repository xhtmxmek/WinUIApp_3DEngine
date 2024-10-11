#include "pch.h"
#include "Renderer/DeferredShadingRenderer.h"
#include "GameThread.h"
#include "Renderer/RenderThread.h"
#include "EngineCore.h"
#include "Common/EngineHelper.h"
#include "EngineCoreBuild.h"
#include "World/World.h"
#include "World/Actor/ActorManager/ActorManager.h"
#include "System/InputManager.h"
#include <fstream>
#include <sstream>
#include "Common/RuntimeContext.h"

namespace Engine
{
	extern void ExitGame() noexcept;

	shared_ptr<EngineCore> enginePtr_;

	void InitEngine()
	{
		enginePtr_ = make_shared<EngineCore>();
	}

	void ReleaseEngine()
	{
		enginePtr_.reset();
	}

	EngineCore* GetRenderingEngine()
	{
		return enginePtr_.get();
	}

#pragma region Initialize
	void EngineCore::Initialize_Inner()
	{
		RuntimeContext::InitialzeRuntimeTable();
		LoadScriptProject(Path::DefaultProjectPath);
	}

	void EngineCore::InitializeCoreThread()
	{
		gameThread = make_unique<GameThread>();
		gameThread->Init();
		renderThread = make_unique<Renderer::RenderThread>();
		renderThread->Init();
	}
#pragma endregion

#pragma region Uninitialize
	void EngineCore::UnInitialize()
	{
		gameThread->Exit();
		renderThread->Exit();

		FreeLibrary(ProjectHandle);
	}
#pragma endregion


#pragma region Active Control
	void EngineCore::Run()
	{
		gameThread->Run();
		renderThread->Run();
	}

	void EngineCore::Stop()
	{

		gameThread->Stop();
		renderThread->Stop();
	}
#pragma endregion

#pragma region Window Message Handlers
	// Message handlers
	void EngineCore::OnActivated()
	{
		// TODO: Game is becoming active window.
	}

	void EngineCore::OnDeactivated()
	{
		// TODO: Game is becoming background window.
	}

	void EngineCore::OnSuspending()
	{
		//gameThread->stop
		renderThread->Stop();
	}

	void EngineCore::OnResuming()
	{		
		gameThread->Run();
		renderThread->Run();
	}

	void EngineCore::OnWindowTransformChanged(const WindowParam& WindowParam_)
	{		
		renderThread->OnWindowTransformChanged(WindowParam_);
	}

	void EngineCore::KeyProcess(SharedTypes::VirtualKey key, bool isPressed)
	{
		Input::InputManager::GetInstance().SetKeyboardState(key, isPressed);
	}

	void EngineCore::PointerProcess(vector<bool> const& pointerState)
	{
		Input::InputManager::GetInstance().SetMouseState(pointerState);
		//pickingLogic
	}

	void EngineCore::PointerProcess(Vector2i pos)
	{
		Input::InputManager::GetInstance().SetMousePos(pos);
	}

	void EngineCore::PointerProcess(int wheelDelta)
	{
		Input::InputManager::GetInstance().SetWheelDelta(wheelDelta);
	}

	void EngineCore::PickCheck(Vector2i screenPos, shared_ptr<World::Actor>& pickedActor)
	{
		//pickedActor = Level::ActorManager::GetInstance().GetActor("MeshTest");
	}

	weak_ptr<World::Actor> EngineCore::GetActor(int index)
	{
		auto world = gameThread->GetWorld();
		return world->GetActor(index);
	}

	weak_ptr<World::Actor> EngineCore::GetActor(const string& name)
	{
		auto world = gameThread->GetWorld();
		return world->GetActor(name);
	}

	size_t EngineCore::GetNumActoRHIst()
	{
		auto world = gameThread->GetWorld();
		return world->GetNumActoRHIst();
	}
#pragma endregion

#pragma region ProjectLoad
	void EngineCore::LoadScriptProject(wstring const& path)
	{
		ProjectHandle = ::LoadLibrary(path.c_str());
		if (ProjectHandle != NULL)
		{
			FreeLibrary(ProjectHandle);
		}
	}
#pragma endregion

}