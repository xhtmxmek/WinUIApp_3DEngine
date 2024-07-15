#pragma once
#include "Common/AsyncWorker.h"
namespace Engine
{
	class GameThread : public AsyncWorker
	{
	public:
		virtual void Init();
		virtual void Run();
		virtual void Stop();
		virtual void Exit();
	};
}
