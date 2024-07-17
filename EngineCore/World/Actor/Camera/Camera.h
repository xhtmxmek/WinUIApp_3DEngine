#pragma once
#include "DLLDefine.h"
#include "Level/Actor/Actor.h"

namespace Engine
{
	namespace Component
	{
		class CameraComponent;
	}

	namespace World
	{
		class ACamera : public Actor
		{
		public:
			RUNTIME_SUBCLASS(ACamera)
		public:
			//ASprite() = default;
			ENGINE_API ACamera(const std::string& actorName);

			virtual void Init() final;
			virtual void Tick(float elapsedTime) final;
		private:
			std::shared_ptr<Component::CameraComponent> cameraComponent_;

		};
	}
}