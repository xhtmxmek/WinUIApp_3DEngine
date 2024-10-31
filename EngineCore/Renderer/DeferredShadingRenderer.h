#pragma once

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
			void ComputeParticle();
			void RendeLights();
			void RenderTranslucencyPass();
			void RenderHeterogenousVolumes();					
			void RenderPostProcessingPass();
			void RenderHairStrands();
		private:
			weak_ptr<Scene> SceneInfo;
#pragma endregion

		};
	}
}