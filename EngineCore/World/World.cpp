#include "pch.h"
#include "World.h"
#include "Actor/ActorManager/ActorManager.h"
#include "Actor/Actor.h"
//#include "Actor/Sprite.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Component/CameraComponent/CameraComponent.h"
#include "Actor/Camera/Camera.h"

using namespace std;
namespace Engine
{
	namespace World
	{
		WorldObject::WorldObject()
		{
			actorManager_ = make_unique<ActorManager>();			
		}

		void WorldObject::Init()
		{
			defaultCamera_ = CreateActor<ACamera>("DefaultCamera");
		}
		
		void WorldObject::Update(float elapsedTime)
		{
			//��ũ��Ʈ�� init�Ǿ����� �ʴٸ� Init. �̹� init �Ǿ����� update.	
			//��ũ��Ʈ�� �ϴ� ��ӹ޴°ɷ� �غ���. �ƴϸ�.. callBack�� ��Ͻ��Ѽ� ��ũ��Ʈ���� callback�� ȣ���ϱ�.		
			//��ũ��Ʈ������ input ������ ������. ��ũ��Ʈ���� ���콺 �����̼� ��ŭ, Ű���� �����ſ� ���� �Ͽ� ����..
			//Ư�� Value ���� �ִϸ��̼��� �ټ� ����.
			//enable�� Actor�� Update.
			//

			for (int i = 0; i < GetNumActoRHIst(); i++)
			{
				auto actor = GetActor(i);
				
				if (actor.expired() == false && actor.lock() != nullptr)
					actor.lock()->Tick(elapsedTime);
			}
				
			//for (const auto& [key, value] : Actors)
			//	value->Tick(elapsedTime);
		}

		void WorldObject::Render()
		{			
		}
	}
}




