#include "pch.h"
#include "Component/SpriteComponent/SpriteComponent.h"
#include "Sprite.h"
#include "Level/World.h"

namespace Engine
{
	namespace World
	{		
		RUNTIME_CLASS_IMPL(ASprite)					

		ASprite::ASprite(const std::string& actorName)
			:Actor(actorName)			
		{	

			SpriteComp = CreateComponent<Component::SpriteComponent>("Sprite");
			//Actor �����ϴµ����� �׳� ���� ������ �޾Ƽ� ����ֱ�.				
			//��� �ΰ� �ǰ� ����, ȭ�鿡 ������ Ȯ��.
			//�״����� ī�޶� ������Ʈ, ����ƽ �޽� �����ؼ� ȭ�� ������ Ȯ��.
			//�״����� assimp ������ ���̱�, ���� Ȯ��.
			//�״����� å ����������.
			//�̹��ֱ��� assimp ������ �ٿ�����.
		}
		void ASprite::Init()
		{
		}

		void ASprite::Tick(float elapsedTime)
		{			
		}
		
	}
}



