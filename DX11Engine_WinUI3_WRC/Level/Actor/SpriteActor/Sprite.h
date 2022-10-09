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

		class ENGINE_API ASprite : public Actor
		{				
		public:
			RUNTIME_SUBCLASS(Actor)
		public:
			//ASprite() = default;
			ASprite(const std::string& actorName);			

			virtual void Init() final;
			virtual void Tick(float elasedTime) final;	
		private:
			SharedPointer<Component::SpriteComponent> SpriteComp;
			
		};
	}
}