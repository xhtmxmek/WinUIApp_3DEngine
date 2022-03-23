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
			DrawActors.clear();
		}

		void World::Update(float fElapsedTime)
		{
			//enable¿Œ Actor∏∏ Update
			for_each(Actors.begin(), Actors.end(),
				[=](const std::shared_ptr<Actor>& actor) { if (actor && actor->IsVisible()) actor->Update(fElapsedTime); });

			CheckVisibilityActors();
		}

		void World::Render()
		{
			std::for_each(DrawActors.begin(), DrawActors.end(),
				[](const std::shared_ptr<Actor>& drawActor) { if (drawActor) drawActor->Render(); });
		}

		std::shared_ptr<Actor> World::CreateActor(const string& name, UINT layerMask)
		{

			return std::shared_ptr<Actor>();
		}

		void World::CheckVisibilityActors()
		{
			DrawActors.reserve(Actors.size());

			//is visible?
			//
			//frustom culling

			//occlusion culling
		}
	}
}




