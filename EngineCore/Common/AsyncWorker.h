#pragma once

namespace Engine
{
	class AsyncWorker
	{
	public:
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;
		virtual void Pause() = 0;
	};
}
