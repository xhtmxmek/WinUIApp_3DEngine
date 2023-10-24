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
			Impl�� ���� ������ ������ ����. ��ӱ����� Actor��. ������Ʈ �����ص� ���� ���빰�� Impl�� ������ ����.
			������Ʈ�� �����͵� Impl�� ������ ������
			��ũ�η� Component �����ϸ� Impl�� Get, Set ȣ���ϵ��� �ϱ�
			������Ʈ �̸��� ()������ȣ���, Impl�� ������ƮGet ������ ȣ��.
			Spirte()�� Impl�� Get, Sprite("")�� Impl�� Set
			��ũ�η� ������Ʈ ������ ������ ������, ������Ʈ �̸����� pImpl�� Get, Set�Լ��� ���۸� ����.
			��ũ�η� ������ ������ ������, ���� �̸����� pImpl�� Get, Set�Լ��� ���۸� ����.
			��ũ�η� �Լ��� ������ ������, �Լ� �̸��� ���ڷ�, pImpl�� ������ �Լ����� ����.
			*/



			Mesh = CreateComponent<Component::StaticMeshComponent>("StaticMesh");
			SetRootComponent(Mesh);
			//Sprite(CreateComponent<Component::SpriteComponent>("Sprite"));

			//��� �ΰ� �ǰ� ����, ȭ�鿡 ������ Ȯ��.
			//�״����� ī�޶� ������Ʈ, ����ƽ �޽� �����ؼ� ȭ�� ������ Ȯ��.
			//�״����� assimp ������ ���̱�, ���� Ȯ��.
			//�״����� å ����������.
			//�̹��ֱ��� assimp ������ �ٿ�����.
		}
		AStaticMesh::~AStaticMesh()
		{
			//delete pImpl;
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



