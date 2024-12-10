#include "pch.h"
#include "DeferredShadingRenderer.h"
#include "RendererBaseHeader.h"
#include "RenderThread.h"

namespace Engine
{
	namespace Renderer
	{
		void RenderThread::Init()
		{
			sceneRenderer = make_unique<DeferredShadingRenderer>();
			RHI::InitRenderResources();
		}

		void RenderThread::Run()
		{
			activate = true;

			if (worker.joinable())
				return;


			//if(Pre Frame GameThread Is still Working, pause for sync)

			worker = thread([this]()
				{
					while (activate)
					{
						std::scoped_lock<std::mutex> lock(renderMutex);
						sceneRenderer->Render();
					}
				});
		}

		void RenderThread::Stop()
		{
			activate = false;
			worker.join();
			RHI::ClearRenderResources();
		}

		void RenderThread::Exit()
		{
			RHI::ReleaseRenderResources();
		}

		void RenderThread::OnWindowTransformChanged(const WindowParam& param)
		{
			std::scoped_lock<std::mutex> lock(renderMutex);
			RHI::ApplyWindowTransform(param);
		}

		void RenderThread::PostInitialize_Inner()
		{
			RHI::PostInitialize();
		}
	}
}

