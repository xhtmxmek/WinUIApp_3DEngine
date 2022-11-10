#pragma once
#include "Level/Component/ComponentBase/ComponentBase.h"
#include "Common/Property/PropertyBase.h"

namespace Engine
{
	namespace Component
	{		
		class StaticMeshComponent : public DrawableComponent
		{
			enum class primitiveType
			{

			};
		public:
			RUNTIME_SUBCLASS(StaticMeshComponent)
			ENGINE_API StaticMeshComponent(const std::string& name = "StaticMeshComponent");
			ENGINE_API ~StaticMeshComponent();
			void Init() final;
			void Tick(float elapsedTime) final;
			void Draw() final;			
		private:			
			unique_ptr<DirectX::GeometricPrimitive> staticMeshShape_;
			ENGINE_PROPERTY()
		};


	}
}
