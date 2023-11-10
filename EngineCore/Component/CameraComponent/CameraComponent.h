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
			virtual void Init() override;
			virtual void Tick(float elapsedTime) override;

			const Matrix4x4f& GetViewMatrix()
			{
				return viewMatrix_;
			}

			const Matrix4x4f& GetProjMatrix()
			{
				return projMatrix_;
			}

		private:
			void ProcessInput(float elapsedTime);
			void MoveFoward(float directionFactor, float elapsedTime = 0.f);
			void MoveRight(float directionFactor, float elapsedTime = 0.f);
			void LookAt();
			void UpdateConstantBuffer();
		private:
			std::map<SharedTypes::VirtualKey, std::function<void(float)>> keyMap_;
			Matrix4x4f viewMatrix_;
			Matrix4x4f projMatrix_;
			bool cameraMoveSwitch_;
			Vector3f focusPoint_;
			Vector3f upVector_;

			PropertyBool useBlur_; //����Ʈ ���μ��� �÷��״� ���Ŀ� PropertyBitmask Ÿ�� ���� �װɷ� �ٲܲ���
		};
	}
}

