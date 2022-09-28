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


			/*
			Impl이 실제 내용을 가지고 있음. 상속구조는 Actor임. 컴포넌트 생성해도 실제 내용물은 Impl이 가지고 있음.
			컴포넌트의 포인터도 Impl이 리턴한 포인터
			매크로로 Component 선언하면 Impl의 Get, Set 호출하도록 하기
			컴포넌트 이름의 ()연산자호출시, Impl의 컴포넌트Get 연산자 호출.
			Spirte()는 Impl의 Get, Sprite("")는 Impl의 Set			
			매크로로 컴포넌트 변수를 설정해 놓으면, 컴포넌트 이름으로 pImpl의 Get, Set함수의 래퍼를 선언.
			매크로로 변수를 설정해 놓으면, 변수 이름으로 pImpl의 Get, Set함수의 래퍼를 선언.			
			매크로로 함수를 설정해 놓으면, 함수 이름과 인자로, pImpl의 동일한 함수명을 선언.			
			*/




			//Component를 내부적으로 생성.
			//Component를 추가는 Impl에 되어야함.
			//pImpl = new SpriteImpl(CreateComponent<Component::SpriteComponent>("Sprite"));
			pImpl = new SpriteImpl();				
			//매크로로 집어넣기. 아니면 Component로 생성한 애들은 Impl에 자동화해서 들어가도록 만들기.
			//SpriteComponent를 생성하면 SpriteImpl에 해당포인터를 넘겨줘야됨
			Sprite(CreateComponent<Component::SpriteComponent>("Sprite"));			
			//Actor 생성하는데에서 그냥 월드 포인터 받아서 집어넣기.				
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
			pImpl->Init();
		}

		void ASprite::Tick(float elapsedTime)
		{
			pImpl->Tick(elapsedTime);
		}

		IMPL_CLASS_PROPERTY_DEFEINITION(ASprite, std::shared_ptr<Component::SpriteComponent>, Sprite)
	}
}



