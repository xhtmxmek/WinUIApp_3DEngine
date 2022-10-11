#pragma once
#include "DLLDefine.h"
#include "../Actor.h"
#include "Common/pImplClassDefine.h"

namespace Engine
{			
	namespace Component
	{
		class SpriteComponent;
	}

	namespace Level
	{		
		class SpriteImpl;

		class ASprite : public Actor
		{				
		public:
			RUNTIME_SUBCLASS(Actor)
		public:
			//ASprite() = default;
			ENGINE_API ASprite(const std::string& actorName);

			ENGINE_API virtual void Init() final;
			virtual void Tick(float elasedTime) final;	
		private:
			shared_ptr<Component::SpriteComponent> SpriteComp;
			
		};
	}
}