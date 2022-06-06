#pragma once
#include "DLLDefine.h"
#include "Actor.h"

namespace Engine
{			
	namespace Component
	{
		class SpriteComponent;
	}

	namespace Level
	{		
		class ENGINE_API ASprite : public Actor
		{
		public:
			RUNTIME_SUBCLASS(Actor)
		public:
			//ASprite() = default;
			ASprite(const std::string& actorName);

			void Init() final;
			void Tick(float elasedTime) final;
		private:
			Component::SpriteComponent* Batch;
		};
	}
}