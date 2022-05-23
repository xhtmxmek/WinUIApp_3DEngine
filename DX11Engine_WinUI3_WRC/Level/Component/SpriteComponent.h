#pragma once
#include "ComponentBase.h"

namespace Engine
{
	namespace Level
	{
		class SpriteComponent : public DrawableComponent
		{
		public:
			SpriteComponent();
			void Init() final;			
			void Tick(float elasedTime) final;
			void Draw() final;
		private:
			bool		Visible;
			std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		};
	}
}