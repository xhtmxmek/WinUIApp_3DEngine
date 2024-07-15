#include "pch.h"
#include "DeferredShadingRenderer.h"
#include "RenderThread.h"

namespace Engine
{
	namespace Renderer
	{
		void RenderThread::Init()
		{
			scene_renderer = make_unique<DeferredShadingRenderer>();
		}

		void RenderThread::Run()
		{
			activate = true;

			if (worker.joinable())
				return;

			worker = thread([this]()
				{
					while (activate)
					{
						std::scoped_lock<std::mutex> lock(EngineTickMutex);
						scene_renderer->Render();												
					}
				});
		}

		void RenderThread::Stop()
		{
		}

		void RenderThread::Exit()
		{
		}


	}
}
