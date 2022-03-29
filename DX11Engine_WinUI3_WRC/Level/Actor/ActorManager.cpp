#include "pch.h"
#include "ActorManager.h"
#include "Actor.h"

namespace Engine
{
	namespace Level
	{
		ActorManager::ActorManager()
			:CurrentActorSizeFactor(1),
			ActorListResized(false)
		{
		}

		void ActorManager::CheckActorListCapacity()
		{
			//Actor�� ���� �Ӱ谪 �̻� ��ŭ ������û�� �ð�쿡�� Actorlist�� ����� �÷��� �Ŀ� Copy�Ѵ�
			if (Actors.size() % ActorsSizeUnit < (ActorsSizeUnit - ActorSizeBias))
				ActorListResized = false;
			else
			{
				if (!ActorListResized)
				{
					std::unordered_map<std::string, std::shared_ptr<Actor>> tempActors;
					tempActors.reserve(CurrentActorSizeFactor * ActorsSizeUnit);
					tempActors.insert(Actors.begin(), Actors.end());					
					Actors.reserve(CurrentActorSizeFactor * ActorsSizeUnit);
					Actors.insert(tempActors.begin(), tempActors.end());					

					ActorListResized = true;
					CurrentActorSizeFactor++;
				}
			}
		}

		void ActorManager::Init()
		{
			Actors.reserve(ActorsSizeUnit);
		}
	}
}