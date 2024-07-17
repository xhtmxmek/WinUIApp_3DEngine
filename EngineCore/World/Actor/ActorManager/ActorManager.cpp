#include "pch.h"
#include "ActorManager.h"
#include "../Actor.h"
#include "../DefaultActor.h"

namespace Engine
{
	namespace World
	{
		void ActorManager::CheckActorListCapacity()
		{
			//Actor�� ���� �Ӱ谪 �̻� ��ŭ ������û�� �ð�쿡�� Actorlist�� ����� �÷��� �Ŀ� Copy�Ѵ�
			if (Actors.size() % ActorsSizeUnit < (ActorsSizeUnit - ActorSizeBias))
				ActorListResized = false;
			else
			{
				if (!ActorListResized)
				{
					unordered_map<string, shared_ptr<Actor>> tempActors;
					tempActors.reserve(CurrentActorSizeFactor * ActorsSizeUnit);
					tempActors.insert(Actors.begin(), Actors.end());
					Actors.reserve(CurrentActorSizeFactor * ActorsSizeUnit);
					Actors.insert(tempActors.begin(), tempActors.end());
					
					actorNames_.reserve(CurrentActorSizeFactor * ActorsSizeUnit);

					ActorListResized = true;
					CurrentActorSizeFactor++;
				}
			}
		}

		shared_ptr<Actor> ActorManager::CreateActor(const std::string& className, const std::string& instanceName)
		{
			auto iter = Actors.find(instanceName.c_str());
			if (iter == Actors.end())
			{
				Level::Actor* runtimeActor = static_cast<Level::Actor*>(RuntimeContext::New(className, instanceName));
				runtimeActor->ImplClassName(className);
				shared_ptr<Level::Actor> ptr(runtimeActor);
				Actors.insert(std::make_pair(instanceName, ptr));
				actorNames_.push_back(instanceName);
				return ptr;
			}
			else
				return iter->second;
		}

		weak_ptr<Actor> ActorManager::GetActor(const std::string& actorName)
		{
			auto iter = Actors.find(actorName.c_str());
			if (iter != Actors.end())
				return iter->second;

			auto ptr = make_shared<ADefaultActor>("Test");
			ptr.reset();
			return ptr;
		}

		weak_ptr<Actor> ActorManager::GetActor(unsigned int index)
		{
			if (index < actorNames_.size())
			{
				auto iter = Actors.find(actorNames_[index]);
				return iter->second;
			}
				
			auto ptr = make_shared<ADefaultActor>("Test");
			ptr.reset();
			return ptr;
		}

		void ActorManager::ReleaseInstance()
		{
			Actors.clear();
		}

		void ActorManager::Init()
		{
		}

		size_t ActorManager::GetNumActorList()
		{
			return Actors.size();
		}
	}
}