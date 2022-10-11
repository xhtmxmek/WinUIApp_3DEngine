#pragma once
#include "DLLDefine.h"
//#include "World.h"
namespace Engine
{
	namespace Level
	{
		class World;		

		class SLevel
		{
		public:
			SLevel(const SLevel&) = delete;
			SLevel& operator=(const SLevel&) = delete;

			ENGINE_API static const shared_ptr<World>& GetWorld(){ return GetInstance().OwningWorld; }
			ENGINE_API static void SetWorld(const shared_ptr<World> world) { GetInstance().OwningWorld = world; }
			void ReleaseInstance(){}
		private:
			ENGINE_API SLevel() = default;
			ENGINE_API static SLevel& GetInstance()
			{
				static SLevel level;
				return level;
			}

			static shared_ptr<World> OwningWorld;
		};
	}
}