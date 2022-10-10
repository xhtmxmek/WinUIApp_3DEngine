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

			static const SharedPointer<World>& GetWorld(){ return GetInstance().OwningWorld; }
			static void SetWorld(const SharedPointer<World> world) { GetInstance().OwningWorld = world; }
			void ReleaseInstance(){}
		private:
			SLevel() = default;
			static SLevel& GetInstance()
			{
				static SLevel level;
				return level;
			}

			static SharedPointer<World> OwningWorld;
		};
	}
}