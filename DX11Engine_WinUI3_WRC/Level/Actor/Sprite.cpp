#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent.h"
#include "Sprite.h"

namespace Engine
{
	namespace Level
	{
		RUNTIME_CLASS_IMPL(ASprite)

		ASprite::ASprite(const std::string& actorName)
			:Actor(actorName)
		{
		}
		void ASprite::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//�� �������� ������Ʈ ����ϱ�			
		}

		void ASprite::Tick(float elasedTime)
		{			
		}
	}
}



