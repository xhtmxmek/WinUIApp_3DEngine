#include "EngineMinimal.h"
#include "ActorManager.h"
#include "../Actor.h"

namespace Engine
{
	namespace Level
	{
		ActorManager::ActorManager()
		{			
		}

		ActorManager::~ActorManager()
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

		std::shared_ptr<Actor> ActorManager::CreateActor(const std::string& className, const std::string& instanceName)		
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

		std::shared_ptr<Actor> ActorManager::GetActorByName(const std::string& actorName)
		{
			return nullptr;
		}

		void ActorManager::ReleaseInstance()
		{			
		}

		void ActorManager::Init()
		{
			//pImpl->Init();
		}

		size_t ActorManager::GetNumActorList()
		{
			return Actors.size();
		}
	}
}