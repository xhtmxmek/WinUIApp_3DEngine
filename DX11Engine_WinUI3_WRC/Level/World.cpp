#include "pch.h"
#include "World.h"
#include "Actor/Actor.h"

using namespace std;
namespace Engine
{
	namespace Level
	{
		World::World()
		{
			Actors.clear();
		}

		void World::Update(float fElapsedTime)
		{
			//enable�� Actor�� Update
			//Actors.empty
			//for_each(Actors.begin(), Actors.end(),
			//	[fElapsedTime](auto& element)
			//	{
			//		std::shared_ptr<Actor> currActor = element.second;
			//		if (currActor)
			//			currActor->Tick(fElapsedTime);
			//	});


			CheckVisibilityActors();
		}

		void World::CheckVisibilityActors()
		{
			//DrawActors.reserve(Actors.size());

			//is visible?
			//
			//frustom culling

			//occlusion culling
		}
	}
}




