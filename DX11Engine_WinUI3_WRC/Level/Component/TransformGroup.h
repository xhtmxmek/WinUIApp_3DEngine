#pragma once
#include "EngineProperty.h"
namespace Engine
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
		const Matrix& GetWorld() const { return World; }
		//static TransformGroup const& Identity() { return Identity; }
		static const TransformGroup Identity;
	private:			
		//propVector3 Position ����� �θ� �ѱ��;
		//transform.SetPositon
		//GetPosition
		//���ο��� position �����ҋ�.
		PropertyVector3 Position;
		PropertyVector3 Scale;
		//quat�� ��� 0,0,0,1
		PropertyVector3 Rotation;

		Matrix World;
		Matrix Local;
		//Math::Matrix RotMat;
		//GameObject* Owner;

		void OnChangeTransorm(EngineProperty* property);
		void UpdateTransform(TransformGroup* parent = nullptr );
	};
	
}

