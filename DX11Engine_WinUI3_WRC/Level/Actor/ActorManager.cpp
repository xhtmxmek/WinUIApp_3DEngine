#include "pch.h"
#include "ActorManager.h"

namespace Engine
{
	namespace Level
	{
		void ActorManager::Init()
		{
			Actors.reserve(ActorsSize);
		}
	}
}