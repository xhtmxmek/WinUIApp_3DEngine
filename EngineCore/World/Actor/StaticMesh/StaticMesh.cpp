#include "pch.h"
#include "Component/StaticMeshComponent/StaticMeshComponent.h"
#include "StaticMesh.h"
//#include "SpriteImpl.h"

namespace Engine
{
	namespace World
	{
		RUNTIME_CLASS_IMPL(AStaticMesh)

			AStaticMesh::AStaticMesh(const std::string& actorName)
			:Actor(actorName)
		{

			Mesh = CreateComponent<Component::StaticMeshComponent>("StaticMesh");
			SetRootComponent(Mesh);
		}

		void AStaticMesh::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//�� �������� ������Ʈ ����ϱ�			
			//pImpl->Init();
		}

		void AStaticMesh::Tick(float elapsedTime)
		{
			//pImpl->Tick(elapsedTime);
		}

		//IMPL_CLASS_PROPERTY_DEFEINITION(ASprite, std::shared_ptr<Component::SpriteComponent>, Sprite)
	}
}



