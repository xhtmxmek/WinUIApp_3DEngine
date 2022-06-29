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
			SpriteImpl(const std::shared_ptr<Component::SpriteComponent>& spriteBatch);

			void Init();
			void Tick(float elasedTime);
		private:
			std::shared_ptr<Component::SpriteComponent> SpriteBatch;
			//Component::SpriteComponent* SpriteBatch;
		};
	}
}