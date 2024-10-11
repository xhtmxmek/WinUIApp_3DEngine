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
			RenderThread() = default;

			virtual void Init();
			virtual void Run();
			virtual void Stop();
			virtual void Exit();

			void OnWindowTransformChanged(const WindowParam& param);

			template<typename AppWindowType>
			void PostInitialize(const WindowInitParam<AppWindowType>& initParam)
			{
				AppWindowType::SetWindowInfoToDevice();
				PostInitialize_Inner();
			}
		private:
			void PostInitialize_Inner();
		private:
			std::thread worker;
			bool activate;
			mutex renderMutex;

			unique_ptr<DeferredShadingRenderer> sceneRenderer;
		};
	}
}