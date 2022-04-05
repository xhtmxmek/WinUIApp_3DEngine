#pragma once
#include "ActorComponent.h"

namespace Engine
{
	namespace Component
	{
		class SpriteComponent : public DrawableComponent
		{
		public:
			void Draw() final;
		private:
			bool		Visible;
			std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		};
	}
}