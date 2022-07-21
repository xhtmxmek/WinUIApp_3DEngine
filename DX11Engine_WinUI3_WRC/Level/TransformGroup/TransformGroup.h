#pragma once
#include "DLLDefine.h"
//#include "EngineProperty.h"

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
	namespace Level
	{
		class TransformGroupImpl;

		class ENGINE_API TransformGroup
		{
		public:
			TransformGroup();
			~TransformGroup();
			const DirectX::SimpleMath::Vector3& GetPosition() const;
		private:
			TransformGroupImpl* pImpl;
			//FVector3 test;
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

			//	DirectX::SimpleMath::Matrix World;
			//	DirectX::SimpleMath::Matrix Local;
			//	//Math::Matrix RotMat;
			//	//GameObject* Owner;

			//	//void OnChangeTransorm(EngineProperty* property);
			//	void UpdateTransform(TransformGroup* parent = nullptr );
		};
	}

	
}

