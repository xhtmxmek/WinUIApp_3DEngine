#pragma once
#include "ActorComponent.h"

namespace Engine
{
	namespace Component
	{
		class StaticMeshComponent : public ActorComponent
		{
		public:			
			StaticMeshComponent();			
			void Init() final;
			void Update(float elapsedTime) final;
			void Draw() final;
		private:
			std::unique_ptr<DirectX::GeometricPrimitive> StaticMeshShape;
		};
	}
}
