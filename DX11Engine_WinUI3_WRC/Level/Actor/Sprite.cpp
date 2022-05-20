#include "pch.h"
#include "Sprite.h"
#include "Level/Component/SpriteComponent.h"

namespace Engine
{
	namespace Level
	{
		void Sprite::Init()
		{
			Batch = std::make_unique<Component::SpriteComponent>();
			//¾À ·»´õ·¯¿¡ ÄÄÆ÷³ÍÆ® µî·ÏÇÏ±â
		}

		void Sprite::Tick(float elasedTime)
		{			
		}
	}
}



