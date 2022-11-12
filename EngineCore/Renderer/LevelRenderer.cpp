#include "pch.h"
#include "LevelRenderer.h"
#include "Component/ComponentBase/ComponentBase.h"

namespace Engine
{
	namespace Renderer
	{		
		void LevelRenderer::Render( const vector<shared_ptr<Component::DrawableComponent>>& DrawList )
		{
			//3D ���� �����׸�(������, ���۵� ��� �����ؼ� �׸�)
			//���������� ���� ������ �޾Ƽ� �׸�. Ȥ�� ���尡 �������� �޾Ƽ� �׸�.
			//2D ���ʹ� ��� �׸���? ���Ҽ��ΰ�. �ϴ� ���ʹ� ���� ���� �Ҽ�.
			//�������� drawComponent list�� ������ ���� �׸���.

			for (auto& drawComponent : DrawList )
			{
				if (drawComponent != nullptr)
					drawComponent->Draw();
			}
		}

		LevelRenderer::LevelRenderer()
		{
		}
	}
}

