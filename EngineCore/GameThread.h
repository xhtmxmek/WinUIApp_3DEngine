#pragma once
#include "Common/AsyncWorker.h"
namespace Engine
{
	namespace World
	{
		class WorldObject;
	}
	class StepTimer;
	class GameThread : public AsyncWorker
	{
	public:
		virtual void Init();
		virtual void Run();
		virtual void Stop();
		virtual void Exit();

	public:
		const std::shared_ptr<World::WorldObject>& GetWorld()
		{
			return world;
		}
	private:		
		std::shared_ptr<StepTimer> timer;
		std::shared_ptr<World::WorldObject> world;

	};
}
