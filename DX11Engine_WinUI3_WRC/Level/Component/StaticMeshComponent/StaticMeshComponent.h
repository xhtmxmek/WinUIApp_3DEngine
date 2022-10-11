#pragma once
#include "../ComponentBase/ComponentBase.h"

namespace Engine
{
	namespace Component
	{		
		class StaticMeshComponent : public DrawableComponent
		{
		public:
			RUNTIME_SUBCLASS(StaticMeshComponent)
			ENGINE_API StaticMeshComponent(const std::string& name = "StaticMeshComponent");
			ENGINE_API ~StaticMeshComponent();
			void Init() final;
			void Tick(float elapsedTime) final;
			void Draw() final;			
		private:
			unique_ptr<DirectX::GeometricPrimitive> StaticMeshShape;			
		};


	}
}
