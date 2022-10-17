#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Sprite.h"
#include "Level/World.h"

namespace Engine
{
	namespace Level
	{		
		RUNTIME_CLASS_IMPL(ASprite)					

		ASprite::ASprite(const std::string& actorName)
			:Actor(actorName)			
		{	

			SpriteComp = CreateComponent<Component::SpriteComponent>("Sprite");
			//Actor 생성하는데에서 그냥 월드 포인터 받아서 집어넣기.				
			//요거 두개 되고 나면, 화면에 렌더링 확인.
			//그다음에 카메라 컴포넌트, 스태틱 메시 구현해서 화면 렌더링 확인.
			//그다음에 assimp 임포터 붙이기, 동작 확인.
			//그다음에 책 진도나가기.
			//이번주까지 assimp 임포터 붙여보기.
		}
		void ASprite::Init()
		{
		}

		void ASprite::Tick(float elapsedTime)
		{			
		}
		
	}
}



