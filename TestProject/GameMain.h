#pragma once
#include "EngineAsset/Script/ScriptInterface.h"
#include "EngineAsset/Script/RuntimeContext.h"
namespace Script
{
	class GameMain : public IScriptInterface
	{
	public:
		RUNTIME_SUBCLASS(GameMain)
	public:
		GameMain() = default;
		~GameMain() = default;

		GameMain(GameMain&&) = delete;
		GameMain& operator= (GameMain&&) = delete;

		GameMain(GameMain const&) = delete;
		GameMain& operator= (GameMain const&) = delete;	

		//void Init();
		//void Tick(float elasedTime);

		void Init() final;
		void Tick(float elasedTime) final;

		static void RegisterRuntime();
	};
}