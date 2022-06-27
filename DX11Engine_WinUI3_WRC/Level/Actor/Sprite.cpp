#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent.h"
#include "Sprite.h"
#include "SpriteImpl.h"

namespace Engine
{
	namespace Level
	{
		RUNTIME_CLASS_IMPL(ASprite)

		ASprite::ASprite(const std::string& actorName)
			:Actor(actorName),
			pImpl(new SpriteImpl(actorName))
		{			
			auto ptr = CreateComponent<Component::SpriteComponent>("Sprite");

		}
		void ASprite::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//¾À ·»´õ·¯¿¡ ÄÄÆ÷³ÍÆ® µî·ÏÇÏ±â			
		}

		void ASprite::Tick(float elasedTime)
		{			
		}
	}
}



