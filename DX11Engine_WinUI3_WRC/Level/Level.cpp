#include "EngineMinimal.h"
#include "Level.h"
#include "LevelImpl.h"
#include "World.h"

namespace Engine
{
	namespace Level
	{
		SLevel::SLevel()
		{			
			pImpl = new SLevelImpl();
		}

		void SLevel::ReleaseInstance()
		{
			delete pImpl;
		}

		std::shared_ptr<World> SLevel::GetWorld()
		{
			return pImpl->GetWorld();
		}
	}
}
