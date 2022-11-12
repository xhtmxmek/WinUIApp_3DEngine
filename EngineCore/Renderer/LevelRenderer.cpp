#include "pch.h"
#include "LevelRenderer.h"
#include "Component/ComponentBase/ComponentBase.h"

namespace Engine
{
	namespace Renderer
	{		
		void LevelRenderer::Render( const vector<shared_ptr<Component::DrawableComponent>>& DrawList )
		{
			//3D 액터 먼저그림(포워드, 디퍼드 모드 선택해서 그림)
			//렌더러에서 월드 세팅을 받아서 그림. 혹은 월드가 렌더러를 받아서 그림.
			//2D 액터는 어떻게 그리나? 어디소속인가. 일단 액터는 전부 월드 소속.
			//렌더러는 drawComponent list를 가지고 씬을 그린다.

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

