#include "EngineMinimal.h"
#include "ActorManager.h"
#include "ActorManagerImpl.h"
#include "Actor.h"

namespace Engine
{
	namespace Level
	{
		ActorManager::ActorManager()
		{
			pImpl = new ActorManagerImpl();
		}

		void ActorManager::CheckActorListCapacity()
		{
		}

		std::shared_ptr<Actor> ActorManager::CreateActor(const std::string& className, const std::string& instanceName)		
		{
			return pImpl->CreateActor(className, instanceName);
		}

		std::shared_ptr<Actor> ActorManager::GetActorByName(const std::string& actorName)
		{
			return pImpl->GetActorByName(actorName);
		}

		void ActorManager::Init()
		{
			pImpl->Init();
		}

		size_t ActorManager::GetNumActorList()
		{
			return pImpl->GetNumActorList();
		}
	}
}