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
		class SpriteImpl;

		class ENGINE_API ASprite : public Actor
		{
		public:
			RUNTIME_SUBCLASS(Actor)
		public:
			//ASprite() = default;
			ASprite(const std::string& actorName);
			~ASprite();

			virtual void Init() final;
			virtual void Tick(float elasedTime) final;
		private:
			SpriteImpl* pImpl;
			//std::shared_ptr<Component::SpriteComponent> SpriteBatch;
			//Component::SpriteComponent* SpriteBatch;
		};
	}
}