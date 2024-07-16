#include "pch.h"
#include "GameThread.h"

namespace Engine
{
	void GameThread::Init()
	{
		//system
		Input::InputManager::GetInstance().Initialize();
		Path::InitBasePathes();
		Timer = make_shared<Engine::DX::StepTimer>();

		//object
		m_World = make_shared<Engine::Level::World>();
		Engine::Level::SLevel::SetWorld(m_World);		
		// TODO: Change the timer settings if you want something other than the default variable timestep mode.
		// e.g. for 60 FPS fixed timestep update logic, call:
		/*
		m_timer.SetFixedTimeStep(true);
		m_timer.SetTargetElapsedSeconds(1.0 / 60);
		*/
	}
	void GameThread::Run()
	{
		activate = true;
		Timer->ResetElapsedTime();

		if (worker.joinable())
		return;

		worker = thread([this]()
			{
				while (activate)
				{
					Timer->Tick([&]()
						{
							ProcessInput();
							Update();
						});
				}
			});

		PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

		float elapsedTime = float(Timer->GetElapsedSeconds());

		// TODO: Add your game logic here.
		// Input Update       

		m_World->Update(elapsedTime);

		PIXEndEvent();
	}
	void GameThread::Stop()
	{
	}
	void GameThread::Exit()
	{
		Level::SLevel::GetInstance().ReleaseInstance();
		Level::ActorManager::GetInstance().ReleaseInstance();
		EngineAsset::TextureManager::GetInstance().ReleaseInstance();
	}
	void GameThread::LoadDefaultProject()
	{
		m_World->Init();

		wstring defaultProjFullPath = Path::ProjectDir + L"\\x64\\Debug\\" + Path::ProjectName;
		HMODULE hDll = ::LoadLibrary(defaultProjFullPath.c_str());
		if (hDll != NULL)
		{
			FreeLibrary(hDll);
		}
	}
}