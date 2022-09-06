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

			void SetSpriteBatch(std::shared_ptr<Component::SpriteComponent> ptr);	//���� Get_Set Accessor�� �ٲٱ�
		private:
			std::shared_ptr<Component::SpriteComponent> SpriteBatch;			
		};
	}
}