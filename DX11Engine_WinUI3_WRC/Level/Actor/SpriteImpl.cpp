#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent.h"
#include "SpriteImpl.h"

namespace Engine
{
	namespace Level
	{		
		SpriteImpl::SpriteImpl(const std::string& actorName)			
		:SpriteBatch(nullptr)
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



