#pragma once
#include "Common/RuntimeContext.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Component/Property/PropertyBase.h"
namespace Engine
{
	namespace Asset
	{
		class Mesh;
	}
	namespace Component
	{			
		class PropertyStaticMesh : public PropertyPath
		{
		public:
			PropertyStaticMesh(std::wstring const& name)
				:PropertyPath(name, L"staticMesh")
			{
			}
		};

		class StaticMeshComponent : public DrawableComponent
		{			
		public:
			RUNTIME_SUBCLASS(DrawableComponent)
			ENGINE_API StaticMeshComponent(const std::string& name = "StaticMeshComponent", const std::string& assetDirectory = "");
			ENGINE_API ~StaticMeshComponent();
			virtual void Init() final;
			virtual void finalize();
			virtual void Tick(float elapsedTime) final;
			virtual void AddPrimitiveToScene() override;
			virtual void PostInitialize() override;
		private:			
			shared_ptr<Asset::Mesh> _staticMesh;
			std::string _assetDirectory;
			bool deformable;
		};
	}
}
