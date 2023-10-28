#pragma once
#include "../ComponentBase/ComponentBase.h"

namespace SharedTypes
{
	enum class VirtualKey;
}

namespace Engine
{
	namespace Component
	{
		class CameraComponent : public ComponentBase
		{
		public:
			RUNTIME_SUBCLASS(CameraComponent)
				ENGINE_API CameraComponent(const std::string& name = "CameraComponent");
			ENGINE_API virtual void Init() override;
			virtual void Tick(float elapsedTime) override;
		private:
			void ProcessInput();
			void MoveFoward(float DirectionFactor = 1.f);
			void MoveRight(float DirectionFactor = 1.f);
			void LookAt();
		private:
			std::map<SharedTypes::VirtualKey, std::function<void()>> keyMap_;
			Matrix4x4f viewMatrix_;
			bool cameraMoveSwitch_;
		};
	}
}

