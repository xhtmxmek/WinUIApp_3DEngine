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
		void ActorManager::Init()
		{
			Actors.reserve(ActorsSizeUnit);
		}
	}
}