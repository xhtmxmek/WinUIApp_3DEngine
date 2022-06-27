#include "EngineMinimal.h"
#include "Level.h"
#include "World.h"

namespace Engine
{
	namespace Level
	{
		SLevel::SLevel()
			:OwningWorld(nullptr)
		{
			if (OwningWorld == nullptr)
				OwningWorld = std::make_unique<World>();
		}
	}
}
