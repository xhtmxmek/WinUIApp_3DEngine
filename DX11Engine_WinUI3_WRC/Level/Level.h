#pragma once
#include "DLLDefine.h"
namespace Engine
{
	namespace Level
	{
		class World;
		class SLevelImpl;

		class ENGINE_API SLevel
		{
		public:
			SLevel(const SLevel&) = delete;
			SLevel& operator=(const SLevel&) = delete;

			static SLevel& GetInstance()
			{
				static SLevel level;
				return level;
			}

			std::shared_ptr<World> GetWorld();
			void ReleaseInstance();
		private:
			SLevel();
			SLevelImpl* pImpl;	
		};
	}
}