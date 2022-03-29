#pragma once
#include "EngineProperty.h"
namespace Engine
{
	namespace Component
	{
		class TransformGroup
		{
		public:
			TransformGroup();
			void SetPosition(const Vector3& pos);
			void SetScale(const Vector3& scale);
			void SetRotation(const Vector3& rotation);

			const Vector3& GetPosition() const;
			const Vector3& GetScale() const;
			const Vector3& GetRotation() const;
		private:
			//propVector3 Position 만들고 부모에 넘기기;
			//transform.SetPositon
			//GetPosition
			//내부에서 position 참조할떄.
			PropertyVector3 Position;
			PropertyVector3 Scale;
			PropertyVector3 Rotation;

			Matrix World;
			Matrix Local;
			//Math::Matrix RotMat;
			//GameObject* Owner;

			void OnChangeTransorm(EngineProperty* property);
			void UpdateTransform();
		};
	}
}

