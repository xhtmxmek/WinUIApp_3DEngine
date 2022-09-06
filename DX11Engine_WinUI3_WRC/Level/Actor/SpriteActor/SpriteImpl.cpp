#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "SpriteImpl.h"

namespace Engine
{
	namespace Level
	{		
		SpriteImpl::SpriteImpl()
		:SpriteBatch(nullptr)
		{
			//SpriteBatch = CreateComponent<Component::SpriteComponent>("Sprite");
			
		}

		void SpriteImpl::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//¾À ·»´õ·¯¿¡ ÄÄÆ÷³ÍÆ® µî·ÏÇÏ±â			
		}

		void SpriteImpl::Tick(float elapsedTime)
		{
		}
		void SpriteImpl::SetSpriteBatch(std::shared_ptr<Component::SpriteComponent> ptr)
		{

		}
	}
}



