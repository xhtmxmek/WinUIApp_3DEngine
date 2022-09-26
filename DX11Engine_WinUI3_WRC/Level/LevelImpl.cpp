#include "EngineMinimal.h"
#include "LevelImpl.h"
#include "World.h"

namespace Engine
{
	namespace Level
	{
		SLevelImpl::SLevelImpl()
			:OwningWorld(nullptr)
		{
			if (OwningWorld == nullptr)
				OwningWorld = std::make_shared<World>();
		}
	}
}
