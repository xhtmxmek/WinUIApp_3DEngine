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
		GameMain이 로드될때,엔진이 들고 있는 스크립트 리스트들을 가져와서 dll내의 스크립트랑 매핑을 시켜야함.
		엔진에서 액터가 name이 PlayerUnit 스크립트를 가지고 있으면, GameMain이 로드되는 시점에 PlayerUnit에 대응 되는 스크립트 객체(ex: Script::PlayerUnit같은..)를 만들기.
		스크립트 객체는 템플릿화 안해도됨. 이름으로 검색해서 생성자 호출하기. 런타임 객체에 이름 등록이 되어있어야됨..
		PlayerUnit에 해당하는 이름 검색하여 생성하기. 생성후 엔진쪽 스크립트 인터페이스에 연결시키기.
		각 소스 파일에서 자신의 이름을 등록시키기. Init에서는 등록된 이름으로 검색해서 동적으로 생성.
		*/
		auto sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level ::ASprite>("hello");

		/*
		0. 스크립트 런타임 객체에 스크립트 이름들을 등록해놓기. 스크립트용 클래스들은 인터페이스 상속받아서 구현하기.(자신이 상속받던지, 인터페이스를 구체화시키던지)
		1. 엔진에서 스크립트 이름을가져오기. 스크립트용 런타임 컨텍스트를 통해 해당 클래스 생성.
		2. 엔진의 스크립트 컴포넌트의 인터페이스에 생성한 인터페이스를 연결하기.
		*/
	}

	void GameMain::Tick(float elapsedTime)
	{

	}
}
