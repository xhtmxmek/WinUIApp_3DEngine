#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Common/pImplClassDefine.h"
#include "SpriteImpl.h"

namespace Engine
{
	namespace Level
	{		
		SpriteImpl::SpriteImpl()
		:SpriteComponent(nullptr)
		{
			//SpriteBatch = CreateComponent<Component::SpriteComponent>("Sprite");
			
		}

		void SpriteImpl::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//�� �������� ������Ʈ ����ϱ�			
		}

		void SpriteImpl::Tick(float elapsedTime)
		{
		}
	}
}



