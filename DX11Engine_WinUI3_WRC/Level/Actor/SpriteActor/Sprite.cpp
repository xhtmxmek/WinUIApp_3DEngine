#include "EngineMinimal.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Sprite.h"
#include "SpriteImpl.h"
#include "Level/World.h"

namespace Engine
{
	namespace Level
	{
		RUNTIME_CLASS_IMPL(ASprite)

		ASprite::ASprite(const std::string& actorName)
			:Actor(actorName),
			pImpl(nullptr)
		{	
			//Component를 내부적으로 생성.
			//Component를 추가는 Impl에 되어야함.
			//pImpl = new SpriteImpl(CreateComponent<Component::SpriteComponent>("Sprite"));
			pImpl = new SpriteImpl();
			auto ptr = CreateComponent<Component::SpriteComponent>("Sprite");			
			//매크로로 집어넣기. 아니면 Component로 생성한 애들은 Impl에 자동화해서 들어가도록 만들기.
			pImpl->SetSpriteBatch( ptr );
			//Actor 생성하는데에서 그냥 월드 포인터 받아서 집어넣기.
			GetWorld().get()->PushComponent( ptr );
			//요거 두개 되고 나면, 화면에 렌더링 확인.
			//그다음에 카메라 컴포넌트, 스태틱 메시 구현해서 화면 렌더링 확인.
			//그다음에 assimp 임포터 붙이기, 동작 확인.
			//그다음에 책 진도나가기.
			//이번주까지 assimp 임포터 붙여보기.
		}
		ASprite::~ASprite()
		{
			delete pImpl;
		}
		void ASprite::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//씬 렌더러에 컴포넌트 등록하기			
		}

		void ASprite::Tick(float elapsedTime)
		{			
		}
	}
}



