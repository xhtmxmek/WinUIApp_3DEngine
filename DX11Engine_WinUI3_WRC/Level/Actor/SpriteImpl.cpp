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
			//�� �������� ������Ʈ ����ϱ�			
		}

		void SpriteImpl::Tick(float elasedTime)
		{
		}
	}
}



