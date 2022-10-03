#pragma once
		
class GameMain
{
public:
	GameMain() = default;
	~GameMain() = default;

	GameMain(GameMain&&) = delete;
	GameMain& operator= (GameMain&&) = delete;

	GameMain(GameMain const&) = delete;
	GameMain& operator= (GameMain const&) = delete;

	//로컬 파일에서 게임 실행에 필요한 정보들을 불러온다
	void Initialize();
};
	
