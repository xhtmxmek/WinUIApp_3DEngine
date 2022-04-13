#pragma once

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

			void PushDrawableComponent(std::shared_ptr<Component::DrawableComponent> const& component);
			void Render();
		private:
			LevelRenderer();
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponents;	//최대 렌더링 액터를 고정해놓고 쓸까?
		};
	}
}