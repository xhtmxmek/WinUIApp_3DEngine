#include "pch.h"
#include "Camera.h"
#include "Component/CameraComponent/CameraComponent.h"

namespace Engine
{
	namespace World
	{
		RUNTIME_CLASS_IMPL(ACamera)

		ACamera::ACamera(const std::string& actorName)
			:Actor(actorName)
		{
			cameraComponent_ = CreateComponent<Component::CameraComponent>("Camera");
			SetRootComponent(cameraComponent_);
		}
		void ACamera::Init()
		{
		}
		void ACamera::Tick(float elapsedTime)
		{
			cameraComponent_->Tick(elapsedTime);
		}
	}
}