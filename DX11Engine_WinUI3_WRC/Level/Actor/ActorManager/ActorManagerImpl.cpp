#include "EngineMinimal.h"
#include "ActorManagerImpl.h"
#include "../Actor.h"

namespace Engine
{
	namespace Level
	{
		void ActorManagerImpl::Init()
		{
			Actors.reserve(ActorsSizeUnit);
		}

		void ActorManagerImpl::CheckActorListCapacity()
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

		size_t ActorManagerImpl::GetNumActorList()
		{
			return Actors.size();
		}

		std::shared_ptr<Actor> ActorManagerImpl::CreateActor(const std::string& className, const std::string& instanceName)		
		{
			auto iter = Actors.find(instanceName);
			if (iter == Actors.end())
			{
				Level::Actor* runtimeActor = static_cast<Level::Actor*>(RuntimeContext::New(className, instanceName));
				std::shared_ptr<Level::Actor> ptr(runtimeActor);
				Actors.insert(std::make_pair(instanceName, ptr));
				return ptr;
			}
			else
				return iter->second;
		}

		std::shared_ptr<Actor> ActorManagerImpl::GetActorByName(const std::string& actorName)
		{
			return nullptr;
		}
	}
}
