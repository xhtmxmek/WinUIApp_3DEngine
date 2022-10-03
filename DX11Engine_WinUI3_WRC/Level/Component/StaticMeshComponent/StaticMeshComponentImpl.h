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
			void Draw(const Engine::Math::TransformGroup& transform);
		private:
			std::unique_ptr<DirectX::GeometricPrimitive> StaticMeshShape;
		};
	}
}
