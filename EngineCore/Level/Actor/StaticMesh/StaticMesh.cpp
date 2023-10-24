#include "pch.h"
#include "Component/StaticMeshComponent/StaticMeshComponent.h"
#include "StaticMesh.h"
//#include "SpriteImpl.h"

namespace Engine
{
	namespace Level
	{
		RUNTIME_CLASS_IMPL(AStaticMesh)

			AStaticMesh::AStaticMesh(const std::string& actorName)
			:Actor(actorName)
			//pImpl(nullptr)
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



			Mesh = CreateComponent<Component::StaticMeshComponent>("StaticMesh");
			SetRootComponent(Mesh);
			//Sprite(CreateComponent<Component::SpriteComponent>("Sprite"));

			//요거 두개 되고 나면, 화면에 렌더링 확인.
			//그다음에 카메라 컴포넌트, 스태틱 메시 구현해서 화면 렌더링 확인.
			//그다음에 assimp 임포터 붙이기, 동작 확인.
			//그다음에 책 진도나가기.
			//이번주까지 assimp 임포터 붙여보기.
		}
		AStaticMesh::~AStaticMesh()
		{
			//delete pImpl;
		}
		void AStaticMesh::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//씬 렌더러에 컴포넌트 등록하기			
			//pImpl->Init();
		}

		void AStaticMesh::Tick(float elapsedTime)
		{
			//pImpl->Tick(elapsedTime);
		}

		//IMPL_CLASS_PROPERTY_DEFEINITION(ASprite, std::shared_ptr<Component::SpriteComponent>, Sprite)
	}
}



