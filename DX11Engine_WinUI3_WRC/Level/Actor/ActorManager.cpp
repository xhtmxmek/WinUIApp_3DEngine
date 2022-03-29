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
			//Actor가 일정 임계값 이상 만큼 생성요청이 올경우에는 Actorlist의 사이즈를 늘려준 후에 Copy한다
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