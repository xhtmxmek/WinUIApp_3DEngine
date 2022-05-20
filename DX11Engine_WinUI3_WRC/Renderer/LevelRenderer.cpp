#include "pch.h"
#include "LevelRenderer.h"
#include "Level/Component/ActorComponent.h"

namespace Engine
{
	namespace Renderer
	{
		void LevelRenderer::PushDrawableComponent(std::shared_ptr<Component::DrawableComponent> const& component)
		{
			//���������� �׸�������Ʈ�� �׷����� ���� ���δ� ������ �ܺο��� �����Ҽ��ִ�.
			//�ܼ� visible flagüũ�� �ƴ϶�, frustom, occluison culling Ȯ�ε�.. �� ���� ���忡�� ������.
			//���忡�� ���������� visible���θ� �Ǵ��ϰ�, �׸��༮�鸸 �������� push�ϱ�.	
			DrawComponents.push_back(component);
		}

		void LevelRenderer::Update(float fElapsedTime)
		{
		}

		void LevelRenderer::Render()
		{
			//3D ���� �����׸�(������, ���۵� ��� �����ؼ� �׸�)
			//���������� ���� ������ �޾Ƽ� �׸�. Ȥ�� ���尡 �������� �޾Ƽ� �׸�.
			//2D ���ʹ� ��� �׸���? ���Ҽ��ΰ�. �ϴ� ���ʹ� ���� ���� �Ҽ�.
			//�������� drawComponent list�� ������ ���� �׸���.

			for (auto& drawComponent : DrawComponents)
			{
				if (drawComponent)
					drawComponent->Draw();
			}
		}

		LevelRenderer::LevelRenderer()
		{
		}
	}
}

