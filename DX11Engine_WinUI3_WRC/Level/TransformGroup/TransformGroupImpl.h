#pragma once

namespace Engine
{
	namespace Level
	{
		class TransformGroupImpl
		{
		public:
			TransformGroupImpl();
			const DirectX::SimpleMath::Vector3& GetPosition() const { return Position; }
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