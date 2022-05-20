#include "pch.h"
#include "LevelRenderer.h"
#include "Level/Component/ActorComponent.h"

namespace Engine
{
	namespace Renderer
	{
		void LevelRenderer::PushDrawableComponent(std::shared_ptr<Component::DrawableComponent> const& component)
		{
			//렌더러에서 그릴컴포넌트가 그려질지 말지 여부는 렌더러 외부에서 결정할수있다.
			//단순 visible flag체크가 아니라, frustom, occluison culling 확인등.. 이 모든건 월드에서 가능함.
			//월드에서 최종적으로 visible여부를 판단하고, 그릴녀석들만 렌더러에 push하기.	
			DrawComponents.push_back(component);
		}

		void LevelRenderer::Update(float fElapsedTime)
		{
		}

		void LevelRenderer::Render()
		{
			//3D 액터 먼저그림(포워드, 디퍼드 모드 선택해서 그림)
			//렌더러에서 월드 세팅을 받아서 그림. 혹은 월드가 렌더러를 받아서 그림.
			//2D 액터는 어떻게 그리나? 어디소속인가. 일단 액터는 전부 월드 소속.
			//렌더러는 drawComponent list를 가지고 씬을 그린다.

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

