#pragma once

namespace Engine
{
	namespace Math
	{		
		class TransformGroupImpl
		{
		public:
			TransformGroupImpl();
			void SetPosition(const DirectX::SimpleMath::Vector3& pos);
			void SetScale(const DirectX::SimpleMath::Vector3& scale);
			void SetRotation(const DirectX::SimpleMath::Vector3& rotation);

			const DirectX::SimpleMath::Vector3& GetPosition() const;
			const DirectX::SimpleMath::Vector3& GetScale() const;
			const DirectX::SimpleMath::Vector3& GetRotation() const;

			const DirectX::SimpleMath::Matrix& GetWorld() const { return World; }			
			void UpdateTransform(TransformGroup* parent = nullptr);
			static TransformGroup const Default() { return TransformGroup(); }
			
		private:
			DirectX::SimpleMath::Vector3 Position;
			DirectX::SimpleMath::Vector3 Scale;
			//	//quatÀÏ °æ¿ì 0,0,0,1
			DirectX::SimpleMath::Vector3 Rotation;

			DirectX::SimpleMath::Matrix World;
			DirectX::SimpleMath::Matrix Local;
			//	//Math::Matrix RotMat;
			//GameObject* Owner;
		};
	}
}