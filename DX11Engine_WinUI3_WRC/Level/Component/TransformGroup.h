#pragma once
#include "DLLDefine.h"
#include "EngineProperty.h"
#include "Common/EngineMath.h"

namespace DirectX	
{
	namespace SimpleMath
	{
		struct Vector3;
		struct Matrix;
	}
}

namespace Engine
{		
	namespace Component
	{
		class TransformGroup
		{
		public:
			TransformGroup();
		private:
			FVector3 test;
			//	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
			//	void SetScale(const DirectX::SimpleMath::Vector3& scale);
			//	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);

			//	const DirectX::SimpleMath::Vector3& GetPosition() const;
			//	const DirectX::SimpleMath::Vector3& GetScale() const;
			//	const DirectX::SimpleMath::Vector3& GetRotation() const;
			//	const DirectX::SimpleMath::Matrix& GetWorld() const { return World; }
			//	//static TransformGroup const& Identity() { return Identity; }
			//	static const TransformGroup Identity;
			//private:			
			//	//propVector3 Position ����� �θ� �ѱ��;
			//	//transform.SetPositon
			//	//GetPosition
			//	//���ο��� position �����ҋ�.
			//	DirectX::SimpleMath::Vector3 Position;
			//	DirectX::SimpleMath::Vector3 Scale;
			//	//quat�� ��� 0,0,0,1
			//	DirectX::SimpleMath::Vector3 Rotation;

			//	DirectX::SimpleMath::Matrix World;
			//	DirectX::SimpleMath::Matrix Local;
			//	//Math::Matrix RotMat;
			//	//GameObject* Owner;

			//	//void OnChangeTransorm(EngineProperty* property);
			//	void UpdateTransform(TransformGroup* parent = nullptr );
		};
	}

	
}

