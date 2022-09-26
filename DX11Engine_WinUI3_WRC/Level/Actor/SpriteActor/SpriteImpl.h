#pragma once

namespace Engine
{
	namespace Component
	{
		class SpriteComponent;
	}

	namespace Level
	{
		class SpriteImpl 
		{
		public:
			//ASprite() = default;
			SpriteImpl();

			void Init();
			void Tick(float elasedTime);

			GET_SET_ACCESSOR(std::shared_ptr<Component::SpriteComponent>, SpriteComponent);
		private:
			std::shared_ptr<Component::SpriteComponent> SpriteComponent;
		};
	}
}