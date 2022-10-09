#pragma once
#include "DLLDefine.h"
//#include "World.h"
namespace Engine
{
	namespace Level
	{
		class World;		

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

			const SharedPointer<World>& GetWorld(){ return OwningWorld; }
			void ReleaseInstance(){}
		private:
			SLevel() = default;
			SharedPointer<World> OwningWorld;
		};
	}
}