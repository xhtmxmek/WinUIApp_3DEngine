#pragma once
#include "../ComponentBase/ComponentBase.h"

namespace Engine
{
	namespace Component
	{
		class CameraComponent : public ComponentBase
		{
		public:
			RUNTIME_SUBCLASS(CameraComponent)
			ENGINE_API CameraComponent(const std::string& name = "CameraComponent");
			ENGINE_API void Init() final;
			void Tick(float elapsedTime) final;								
		};
	}
}

