#pragma once
#include "DLLDefine.h"
//#include "World.h"

using namespace std;
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

			ENGINE_API static const std::shared_ptr<World>& GetWorld(){ return GetInstance().OwningWorld; }
			ENGINE_API static void SetWorld(const std::shared_ptr<World> world) { GetInstance().OwningWorld = world; }			
			ENGINE_API static SLevel& GetInstance()			
			{
				static SLevel level;
				return level;
			}
			ENGINE_API void ReleaseInstance() { OwningWorld.reset(); }
		private:
			ENGINE_API SLevel() = default;

			static shared_ptr<World> OwningWorld;
		};
	}
}