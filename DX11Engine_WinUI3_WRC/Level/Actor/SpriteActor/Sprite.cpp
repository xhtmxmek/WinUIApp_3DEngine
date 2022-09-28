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
			Impl�� ���� ������ ������ ����. ��ӱ����� Actor��. ������Ʈ �����ص� ���� ���빰�� Impl�� ������ ����.
			������Ʈ�� �����͵� Impl�� ������ ������
			��ũ�η� Component �����ϸ� Impl�� Get, Set ȣ���ϵ��� �ϱ�
			������Ʈ �̸��� ()������ȣ���, Impl�� ������ƮGet ������ ȣ��.
			Spirte()�� Impl�� Get, Sprite("")�� Impl�� Set			
			��ũ�η� ������Ʈ ������ ������ ������, ������Ʈ �̸����� pImpl�� Get, Set�Լ��� ���۸� ����.
			��ũ�η� ������ ������ ������, ���� �̸����� pImpl�� Get, Set�Լ��� ���۸� ����.			
			��ũ�η� �Լ��� ������ ������, �Լ� �̸��� ���ڷ�, pImpl�� ������ �Լ����� ����.			
			*/




			//Component�� ���������� ����.
			//Component�� �߰��� Impl�� �Ǿ����.
			//pImpl = new SpriteImpl(CreateComponent<Component::SpriteComponent>("Sprite"));
			pImpl = new SpriteImpl();				
			//��ũ�η� ����ֱ�. �ƴϸ� Component�� ������ �ֵ��� Impl�� �ڵ�ȭ�ؼ� ������ �����.
			//SpriteComponent�� �����ϸ� SpriteImpl�� �ش������͸� �Ѱ���ߵ�
			Sprite(CreateComponent<Component::SpriteComponent>("Sprite"));			
			//Actor �����ϴµ����� �׳� ���� ������ �޾Ƽ� ����ֱ�.				
			//��� �ΰ� �ǰ� ����, ȭ�鿡 ������ Ȯ��.
			//�״����� ī�޶� ������Ʈ, ����ƽ �޽� �����ؼ� ȭ�� ������ Ȯ��.
			//�״����� assimp ������ ���̱�, ���� Ȯ��.
			//�״����� å ����������.
			//�̹��ֱ��� assimp ������ �ٿ�����.
		}
		ASprite::~ASprite()
		{
			delete pImpl;
		}
		void ASprite::Init()
		{
			//Batch = std::make_unique<Component::SpriteComponent>("");
			//�� �������� ������Ʈ ����ϱ�			
			pImpl->Init();
		}

		void ASprite::Tick(float elapsedTime)
		{
			pImpl->Tick(elapsedTime);
		}

		IMPL_CLASS_PROPERTY_DEFEINITION(ASprite, std::shared_ptr<Component::SpriteComponent>, Sprite)
	}
}



