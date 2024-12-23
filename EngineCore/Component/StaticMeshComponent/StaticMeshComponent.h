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
				//�� Ÿ���� �ּҸ� �Ѱܼ�, ������Ʈ ������Ƽ �θ𿡼� packedValueȣ���Ű��. 
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
			virtual void PostInitialize() override;
		private:			
			std::unique_ptr<DirectX::GeometricPrimitive> staticMeshShape_;			
			PropertyStaticMesh meshType_;
		};
	}
}
