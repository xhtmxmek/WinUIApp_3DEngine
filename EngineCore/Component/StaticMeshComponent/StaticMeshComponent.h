#pragma once
#include "Common/RuntimeContext.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Component/Property/PropertyBase.h"
namespace Engine
{
	namespace Component
	{			
		class PropertyStaticMesh : public PropertyPath
		{
		public:
			//enum MeshType
			//{
			//	Cube = 0,
			//	Sphere,
			//	Cylinder,
			//	Cone,
			//};

			PropertyStaticMesh(std::wstring const& name)
				:PropertyPath(name, L"staticMesh")
			{
				//각 타입의 주소를 넘겨서, 컴포넌트 프로퍼티 부모에서 packedValue호출시키기. 
			}

			//PropertyStaticMesh& operator=(MeshType type)
			//{
			//	PropertyEnum::operator=(static_cast<int>(type));
			//	return *this;
			//}
		};

		class StaticMeshComponent : public DrawableComponent
		{			
		public:
			RUNTIME_SUBCLASS(DrawableComponent)
			ENGINE_API StaticMeshComponent(const std::string& name = "StaticMeshComponent");
			ENGINE_API ~StaticMeshComponent();
			virtual void Init() final;
			virtual void Tick(float elapsedTime) final;
			virtual void Draw() final;
			//void meshType(PropertyStaticMesh::MeshType meshType);
		private:			
			std::unique_ptr<DirectX::GeometricPrimitive> staticMeshShape_;			
			PropertyStaticMesh meshType_;
		};
	}
}
