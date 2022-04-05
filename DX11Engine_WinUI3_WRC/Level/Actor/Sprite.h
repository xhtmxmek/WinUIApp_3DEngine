#pragma once
#include "Actor.h"

namespace Engine
{
	namespace Component
	{
		class SpriteComponent;
	}

	namespace Level
	{
		class Sprite : public Actor
		{
		public:
			Sprite() = default;
			void Init() final;
			void Tick(float elasedTime) final;
		private:
			std::unique_ptr<Component::SpriteComponent> Batch;
		};
	}
}