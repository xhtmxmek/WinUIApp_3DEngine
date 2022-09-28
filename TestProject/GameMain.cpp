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
		//engine�� GameMain�� �Լ� ��������ֱ�. or Engine�� ��ũ��Ʈ�� ��ӹ޾Ƽ� �����. �����Ѱ�?
		auto sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level::ASprite>("hello");
		size_t actorCount = Engine::Level::ActorManager::GetInstance().GetNumActorList();
		int k = 5;
	}

	void GameMain::Tick()
	{

	}
}
