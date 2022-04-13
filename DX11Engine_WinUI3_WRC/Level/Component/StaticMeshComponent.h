#pragma once
#include "ActorComponent.h"

namespace Engine
{
	namespace Component
	{
		class StaticMeshComponent : public DrawableComponent
		{
		public:			
			StaticMeshComponent();			
			void Init() final;
			void Tick(float elapsedTime) final;
			void Draw() final;
		private:
			std::unique_ptr<DirectX::GeometricPrimitive> StaticMeshShape;
		};
	}
}
