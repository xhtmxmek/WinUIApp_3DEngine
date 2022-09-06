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
			//Component�� ���������� ����.
			//Component�� �߰��� Impl�� �Ǿ����.
			//pImpl = new SpriteImpl(CreateComponent<Component::SpriteComponent>("Sprite"));
			pImpl = new SpriteImpl();
			auto ptr = CreateComponent<Component::SpriteComponent>("Sprite");			
			//��ũ�η� ����ֱ�. �ƴϸ� Component�� ������ �ֵ��� Impl�� �ڵ�ȭ�ؼ� ������ �����.
			pImpl->SetSpriteBatch( ptr );
			//Actor �����ϴµ����� �׳� ���� ������ �޾Ƽ� ����ֱ�.
			GetWorld().get()->PushComponent( ptr );
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
		}

		void ASprite::Tick(float elapsedTime)
		{			
		}
	}
}



