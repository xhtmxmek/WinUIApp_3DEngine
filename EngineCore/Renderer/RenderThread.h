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

#pragma region Windows OS dedicated
			void SetSwapChainPanel(const SwapchainPanelInfo& swapchainPanelInfo_);
			void OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo_);
			IDXGISwapChain3* GetSwapChain();
#pragma endregion
			void OnWindowSizeChanged(SharedTypes::Size windowSize);
		private:
			std::thread worker;
			bool activate;
			mutex renderMutex;

			unique_ptr<DeferredShadingRenderer> scene_renderer;
		};
	}
}