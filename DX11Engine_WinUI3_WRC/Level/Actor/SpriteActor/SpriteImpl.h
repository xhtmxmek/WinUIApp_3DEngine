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

			void SetSpriteBatch(std::shared_ptr<Component::SpriteComponent> ptr);	//추후 Get_Set Accessor로 바꾸기
		private:
			std::shared_ptr<Component::SpriteComponent> SpriteBatch;			
		};
	}
}