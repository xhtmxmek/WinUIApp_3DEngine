#include "pch.h"
#include "GameMain.h"

#include <string>
#include <memory>
#include <map>
#include <unordered_map>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include "SimpleMath.h"
//#include "SpriteBatch.h"

#include "Level/Actor/ActorManager/ActorManager.h"
#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Level/Component/StaticMeshComponent/StaticMeshComponent.h"
#include "Common/Math/TransformGroup.h"
#include "Level/World.h"

namespace GameScript
{
	void GameMain::Init()
	{
		//engine에 GameMain의 함수 연결시켜주기. or Engine의 스크립트를 상속받아서 만들기. 가능한가?
		auto sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level::ASprite>("hello");
		size_t actorCount = Engine::Level::ActorManager::GetInstance().GetNumActorList();
		int k = 5;
	}

	void GameMain::Tick()
	{

	}
}
