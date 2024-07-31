#pragma once
//렌더러는 월드에 대한 업데이트와 렌더링을 담당하는 클래스이다. 
//렌더링 파이프라인을 담당하고 있다.
//unique 포인터를 가지고 있으므로, pImpl로 구현하여 상위구조에서 헤더를 알 필요 없도록 해얗


namespace Engine
{
	namespace Component
	{
		class DrawableComponent;
	}

	namespace Renderer
	{
		class Scene;

		class DeferredShadingRenderer
		{
		public:
			DeferredShadingRenderer() = default;
			DeferredShadingRenderer(const DeferredShadingRenderer&) = delete;
			DeferredShadingRenderer& operator=(const DeferredShadingRenderer&) = delete;
			void Stop();

#pragma region Render Scene			
			void Render();			
#pragma endregion
#pragma region Initialize View
		private:
			void InitView();
			void ComputeVisibility();
			void GatherDynamicMesh();
			void OcclusionCull();
			void FrustomCull();
#pragma endregion

#pragma region RenderPasses
			void Clear();
			void RenderShadowDepth();
			void RenderBasePass();
			void RendeRHIghts();
			void RenderTranslucencyPass();
			void RenderVolumetricFog();
			void RenderPostProcessingPass();
		private:
			weak_ptr<Scene> SceneInfo;
#pragma endregion

		};
	}
}