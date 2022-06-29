#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent.h"
#include "SpriteImpl.h"

namespace Engine
{
	namespace Level
	{		
		SpriteImpl::SpriteImpl(const std::shared_ptr<Component::SpriteComponent>& spriteBatch)
		:SpriteBatch(spriteBatch)
		{
			//SpriteBatch = CreateComponent<Component::SpriteComponent>("Sprite");
			
		}
		void SpriteImpl::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//¾À ·»´õ·¯¿¡ ÄÄÆ÷³ÍÆ® µî·ÏÇÏ±â			
		}

		void SpriteImpl::Tick(float elasedTime)
		{
		}
	}
}



