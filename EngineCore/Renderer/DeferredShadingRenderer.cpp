#include "pch.h"
#include "DeferredShadingRenderer.h"
#include "Component/ComponentBase/ComponentBase.h"

namespace Engine
{
	namespace Renderer
	{		
		void DeferredShadingRenderer::Render( const vector<shared_ptr<Component::DrawableComponent>>& DrawList )
		{
			//3D ���� �����׸�(������, ���۵� ��� �����ؼ� �׸�)
			//���������� ���� ������ �޾Ƽ� �׸�. Ȥ�� ���尡 �������� �޾Ƽ� �׸�.
			//2D ���ʹ� ��� �׸���? ���Ҽ��ΰ�. �ϴ� ���ʹ� ���� ���� �Ҽ�.
			//�������� drawComponent list�� ������ ���� �׸���.


			/*
			* ue���� �ڵ带 ������ �������� �����غ���.
			* mesh�������� �� �н� ���� meshProcessor�� �ִ�.
			* meshProcessor�� primitive�� vertex, �� pass�� shader, �� pass���� �غ�Ǿ��ִ� renderstate����
			* �����Ѵ�.
			* �Ϲ������� static mesh�� drawcommand�� ĳ�� �ȴ�. dynamic mesh�� drawcommand�� �������� �����ȴ�.
			* dynamic mesh�� skeletal mesh���� �����ؼ�,fog�� ��ƼŬ ���� �͵��� �ش�ȴ�. 
			* 
			*/

			ComputeVisibility();

			RenderShadowDepth();
			
			RenderBasePass();

			//deferred light, ������ ���� ����
			RenderLights();

			RenderTranslucencyPass();

			//RenderFog..particle.. etc...
			RenderVolumetricFog();

			//���ʿ��� translucency pass composit
			RenderPostProcessingPass();

			for (auto& drawComponent : DrawList )
			{
				if (drawComponent != nullptr)
					drawComponent->Draw();
			}
		}

#pragma region Visibility Check
		void DeferredShadingRenderer::InitView()
		{
			ComputeVisibility();
			GatherDynamicMesh();

		}
		void DeferredShadingRenderer::ComputeVisibility()
		{
			//Scene�� �������ִ� primitive���� visibility �˻�

			/*
			* 1.frustomculling
			* 2.occlusionculling
			* 3.�� drawComponent�� visibility �˻�
			* 4.������ �̿��Ͽ� ���ķ� �˻�
			* 5.��� Primitive �˻��Ͽ�,���ü� ����� Primitive�� DrawCommand�� VisibieCommandList�� ����.
			* 6.���� staticMesh�� ���� ���̸�, Scene�� dinamicMesh�� �˻��Ͽ� ���⼭ �������� ����. 
			* VisibleDrawCommand�� �𸮾󿡼� View�� ������ ����. �츮�� �׳� View��� ����ü ���� ����ְ� ����.
			*/
			OcclusionCull();
			FrustomCull();
		}
		void DeferredShadingRenderer::GatherDynamicMesh()
		{
			//Scene�� Dynamic Mesh�� drawCommand ����
			//View�� visibleDrawCommand�� drawCommand �߰�
			//visibleDrawCommand�� CachedDrawCommands�� �׳� Drawcommands�� �����̴�.
			//visibleDrawCommand�� �� pass���� �ִ�.
		}
		void DeferredShadingRenderer::OcclusionCull()
		{
		}
		void DeferredShadingRenderer::FrustomCull()
		{
		}
#pragma endregion


		void DeferredShadingRenderer::RenderShadowDepth()
		{
		}
		void DeferredShadingRenderer::RenderBasePass()
		{
			/*VisibleDrawCommand�� Draw�Ѵ�. ���ʿ��� ���ķ� Draw�Ѵ�.
			*StaticMesh�� ��������� ������ �ʴ� �� ĳ���ؼ� ��������� ����
			* MeshProcessor�� staticMesh ������ ���ؽ�, pass�� RenderState, pass�� Shader���� �����Ͽ� DrawCommand�� �����.
			* DynamicMesh�� �������� MeshProcessor�� �̿��Ͽ� ���� ����� �����.
			*/
		}
		void DeferredShadingRenderer::RenderLights()
		{
			//����Ʈ�� ���ö���Ʈ, �𷺼ų� ����Ʈ, Ÿ�� �����ִ�.
			//�۷ι��Ϸ�̳��̼��� �н� �Ŀ� �����غ���.
		}
		void DeferredShadingRenderer::RenderTranslucencyPass()
		{
			/*Todo
			* �������� ��Į�� ����
			* pp�� ������ġ�� ���Եɼ� �ִ� ������ �н����� ����.�̰� ���� �ʿ��ϸ� �ֱ�
			* ������ ���������� �� ��. ���͵� �ʿ�.
			*/
		}
		void DeferredShadingRenderer::RenderVolumetricFog()
		{
			/*
			* volume ������ ���� �ʿ�. Ư�� fog
			*/
		}
		void DeferredShadingRenderer::RenderPostProcessingPass()
		{
			/*
			* UE���� post process�� ������ �����Ǿ�����. ��κ��� ��ǻƮ ���̴��� �������.
			*/
		}
	}
}

