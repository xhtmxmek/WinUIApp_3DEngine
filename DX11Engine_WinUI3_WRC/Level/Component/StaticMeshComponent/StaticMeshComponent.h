#pragma once
#include "../ComponentBase/ComponentBase.h"

namespace Engine
{
	namespace Component
	{		
		class ENGINE_API StaticMeshComponent : public DrawableComponent
		{
		public:
			RUNTIME_SUBCLASS(StaticMeshComponent)
			StaticMeshComponent(const std::string& name = "StaticMeshComponent");
			~StaticMeshComponent();
			void Init() final;
			void Tick(float elapsedTime) final;
			void Draw() final;			
		private:
			UniquePointer<DirectX::GeometricPrimitive> StaticMeshShape;			
		};


	}
}
