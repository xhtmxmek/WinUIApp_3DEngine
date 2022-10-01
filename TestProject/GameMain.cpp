#include "pch.h"
#include "GameMain.h"

#include <string>
#include <memory>
#include <map>
#include <unordered_map>

#include "SimpleMath.h"
//#include "SpriteBatch.h"

#include "Level/Actor/ActorManager/ActorManager.h"
#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Level/Component/ScriptComponent/ScriptComponent.h"
#include "Common/Math/TransformGroup.h"
#include "Level/World.h"

namespace Script
{
	//REGISTER_RUNTIME_TEST(GameMain)
	//Script::RuntimeContext::RuntimeClassTable
	//GameMain::RegisterRuntime();
	//void(Script::GameMain::*fp)() = &GameMain::Init;
	RuntimeContext::Regist()

	void GameMain::Init()
	{
		/*
		GameMain�� �ε�ɶ�,������ ��� �ִ� ��ũ��Ʈ ����Ʈ���� �����ͼ� dll���� ��ũ��Ʈ�� ������ ���Ѿ���.
		�������� ���Ͱ� name�� PlayerUnit ��ũ��Ʈ�� ������ ������, GameMain�� �ε�Ǵ� ������ PlayerUnit�� ���� �Ǵ� ��ũ��Ʈ ��ü(ex: Script::PlayerUnit����..)�� �����.
		��ũ��Ʈ ��ü�� ���ø�ȭ ���ص���. �̸����� �˻��ؼ� ������ ȣ���ϱ�. ��Ÿ�� ��ü�� �̸� ����� �Ǿ��־�ߵ�..
		PlayerUnit�� �ش��ϴ� �̸� �˻��Ͽ� �����ϱ�. ������ ������ ��ũ��Ʈ �������̽��� �����Ű��.
		�� �ҽ� ���Ͽ��� �ڽ��� �̸��� ��Ͻ�Ű��. Init������ ��ϵ� �̸����� �˻��ؼ� �������� ����.
		*/
		auto sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level ::ASprite>("hello");

		/*
		0. ��ũ��Ʈ ��Ÿ�� ��ü�� ��ũ��Ʈ �̸����� ����س���. ��ũ��Ʈ�� Ŭ�������� �������̽� ��ӹ޾Ƽ� �����ϱ�.(�ڽ��� ��ӹ޴���, �������̽��� ��üȭ��Ű����)
		1. �������� ��ũ��Ʈ �̸�����������. ��ũ��Ʈ�� ��Ÿ�� ���ؽ�Ʈ�� ���� �ش� Ŭ���� ����.
		2. ������ ��ũ��Ʈ ������Ʈ�� �������̽��� ������ �������̽��� �����ϱ�.
		*/
	}

	void GameMain::Tick(float elapsedTime)
	{

	}
}
