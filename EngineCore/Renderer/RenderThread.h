#pragma once

#include "Common/AsyncWorker.h"

namespace Engine
{
	namespace Renderer
	{
		class DeferredShadingRenderer;

		class RenderThread : public AsyncWorker
		{
		public:
			virtual void Init();
			virtual void Run();
			virtual void Stop();
			virtual void Exit();

			const mutex& GetMutex()
			{
				return renderMutex;
			}
		private:
			std::thread worker;
			bool activate;
			mutex renderMutex;

			unique_ptr<DeferredShadingRenderer> scene_renderer;
		};
	}
}