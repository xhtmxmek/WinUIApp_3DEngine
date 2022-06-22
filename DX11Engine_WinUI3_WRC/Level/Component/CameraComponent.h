#pragma once
#include "ComponentBase.h"

namespace Engine
{
	namespace Component
	{
		class CameraComponent : public ComponentBase
		{
		public:
			RUNTIME_SUBCLASS(CameraComponent)
			CameraComponent(const std::string& name = "CameraComponent");
			void Init() final;
			void Tick(float elapsedTime) final;								
		};
	}
}

