#pragma once
//�������� ���忡 ���� ������Ʈ�� �������� ����ϴ� Ŭ�����̴�. 
//������ ������������ ����ϰ� �ִ�.
//���尡 �������� �����ϴ°�? �������� ���带 �����ϴ°�?

namespace Engine
{
	namespace Component
	{
		class DrawableComponent;
	}

	namespace Renderer
	{
		class DeferredShadingRenderer
		{
		public:
			static DeferredShadingRenderer& GetInstance()
			{
				static DeferredShadingRenderer instance;
				return instance;
			}
			
			DeferredShadingRenderer(const DeferredShadingRenderer& ) = delete;
			DeferredShadingRenderer& operator=(const DeferredShadingRenderer& ) = delete;

			void Render(const vector<shared_ptr<Component::DrawableComponent>>& drawList );
		private:
			DeferredShadingRenderer() = default;
#pragma region Initialize View
			void InitView();
			void ComputeVisibility();
			void GatherDynamicMesh();
			void OcclusionCull();
			void FrustomCull();
#pragma endregion
			void RenderShadowDepth();
			void RenderBasePass();
			void RenderLights();
			void RenderTranslucencyPass();
			void RenderVolumetricFog();
			void RenderPostProcessingPass();
		};
	}
}