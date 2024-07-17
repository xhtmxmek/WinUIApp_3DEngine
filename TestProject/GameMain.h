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

	//���� ���Ͽ��� ���� ���࿡ �ʿ��� �������� �ҷ��´�
	void Initialize();
};
	
