#pragma once

namespace Engine
{
	namespace Component
	{
		class StaticMeshComponentImpl
		{
		public:
			StaticMeshComponentImpl() = default;
			void Init();
			void Tick(float elapsedTime);
			void Draw();
		private:
			std::unique_ptr<DirectX::GeometricPrimitive> StaticMeshShape;
		};
	}
}
