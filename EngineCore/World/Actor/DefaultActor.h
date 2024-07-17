#pragma once
#include "DLLDefine.h"
#include "Level/Actor/Actor.h"

namespace Engine
{
	namespace Component
	{
		class StaticMeshComponent;
	}

	namespace World
	{
		class ADefaultActor : public Actor
		{
		public:
			RUNTIME_SUBCLASS(DefaultActor)
		public:
			//ASprite() = default;
			ENGINE_API ADefaultActor(const std::string& actorName);
			ENGINE_API ~ADefaultActor();

			virtual void Init() final;
			virtual void Tick(float elasedTime) final;

		};
	}
}