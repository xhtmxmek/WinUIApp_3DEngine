#pragma once
//렌더러는 월드에 대한 업데이트와 렌더링을 담당하는 클래스이다. 
//렌더링 파이프라인을 담당하고 있다.
//엔진이 렌더러를 소유. 렌더러는 월드의 렌더러 모듈 버전인 씬을 소유.


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
			static DeferredShadingRenderer& GetInstance()
			{
				static DeferredShadingRenderer instance;
				return instance;
			}

			DeferredShadingRenderer(const DeferredShadingRenderer&) = delete;
			DeferredShadingRenderer& operator=(const DeferredShadingRenderer&) = delete;

			void Render(const vector<shared_ptr<Component::DrawableComponent>>& drawList);
		private:
			DeferredShadingRenderer() = default;
#pragma region Initialize View
			void InitView();
			void ComputeVisibility();
			void GatherDynamicMesh();
			void OcclusionCull();
			void FrustomCull();
#pragma endregion

#pragma region Render Scene
			void RenderShadowDepth();
			void RenderBasePass();
			void RenderLights();
			void RenderTranslucencyPass();
			void RenderVolumetricFog();
			void RenderPostProcessingPass();

			unique_ptr<Scene> SceneInfo; 
#pragma endregion

		};
	}
}