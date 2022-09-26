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
			IMPL_CLASS_PROPERTY(std::shared_ptr<Component::SpriteComponent>, SpriteComponent);
		public:
			RUNTIME_SUBCLASS(Actor)
		public:
			//ASprite() = default;
			ASprite(const std::string& actorName);
			~ASprite();

			virtual void Init() final;
			virtual void Tick(float elasedTime) final;
		private:
			map<string, string> mapTest;
			string testTypeMember;
			SpriteImpl* pImpl;
			//GET_SET_IMPL_ACCESSOR(std::shared_ptr<Component::SpriteComponent>, SpriteBatch);			
			//std::shared_ptr<Component::SpriteComponent> SpriteBatch;
			//Component::SpriteComponent* SpriteBatch;		
			
		};
	}
}