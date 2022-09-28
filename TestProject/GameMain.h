#pragma once
namespace GameScript
{
	class GameMain
	{
	public:
		GameMain() = default;
		~GameMain() = default;

		GameMain(GameMain&&) = delete;
		GameMain& operator= (GameMain&&) = delete;

		GameMain(GameMain const&) = delete;
		GameMain& operator= (GameMain const&) = delete;

		void Init();
		void Tick();
	};
}