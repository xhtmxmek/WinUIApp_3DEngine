#pragma once
//렌더러는 월드에 대한 업데이트와 렌더링을 담당하는 클래스이다. 
//렌더링 파이프라인을 담당하고 있다.
//월드가 렌더러를 소유하는가? 렌더러가 월드를 소유하는가?

namespace Engine
{
	namespace Component
	{
		class DrawableComponent;
	}

	namespace Renderer
	{
		class LevelRenderer
		{
		public:
			static LevelRenderer& GetInstance()
			{
				static LevelRenderer instance;
				return instance;
			}
			
			LevelRenderer(const LevelRenderer& ) = delete;
			LevelRenderer& operator=(const LevelRenderer& ) = delete;

			void Render(const vector<shared_ptr<Component::DrawableComponent>>& drawList );
		private:
			LevelRenderer();			
		};
	}
}