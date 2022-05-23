#pragma once
#include "Actor.h"

namespace Engine
{			
	namespace Level
	{
		class SpriteComponent;

		class Sprite : public Actor
		{
		public:
			Sprite() = default;
			void Init() final;
			void Tick(float elasedTime) final;
		private:
			std::unique_ptr<SpriteComponent> Batch;
		};
	}
}