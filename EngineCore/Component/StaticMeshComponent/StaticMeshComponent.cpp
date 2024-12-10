#include "pch.h"
#include "StaticMeshComponent.h"
#include "EngineAsset/Mesh.h"
#include "Renderer/MeshRendering.h"
#include "Renderer/Resource/DeviceContext.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(StaticMeshComponent)

		StaticMeshComponent::StaticMeshComponent(const std::string& name, const std::string& assetDirectory)
			:DrawableComponent(name),
			_assetDirectory(assetDirectory)
		{
			//typeName_ = "StaticMeshComponent";
			SetVisible(true);
		}

		StaticMeshComponent::~StaticMeshComponent()
		{			
		}

		void StaticMeshComponent::Init()
		{
			//spawn될때 staticMesh resource 정보를 로드한다.
			// 
			//auto context = DeviceContextWrapper::GetDeviceContext()->GetD3DDeviceContext();
			//staticMeshShape_ = DirectX::GeometricPrimitive::CreateSphere(context);

			//meshType_.Register(L"Cube", PropertyStaticMesh::MeshType::Cube);
			//meshType_.Register(L"Sphere", PropertyStaticMesh::MeshType::Sphere);
			//meshType_.Register(L"Cylinder", PropertyStaticMesh::MeshType::Cylinder);
			//meshType_.Register(L"Cone", PropertyStaticMesh::MeshType::Cone);
									
			//AddProperty(&meshType_);
			_staticMesh = make_shared<Asset::Mesh>();
			_staticMesh->Load(_assetDirectory);
		}

		void StaticMeshComponent::finalize()
		{
			_staticMesh->Unload();
			_staticMesh.reset();
		}

		void StaticMeshComponent::Tick(float elapsedTime)
		{			
		}

		void StaticMeshComponent::AddPrimitiveToScene()
		{
			//Create Mesh Info. Rendering Info.(vertex,index, material...)
			//In RenderingThread, MeshProcessor is created by MeshInfo. Meshprocessor just making drawCommand function's wrapper.
			Renderer::MeshInfo meshInfo;
		}

		void StaticMeshComponent::PostInitialize()
		{
			AddPrimitiveToScene();
		}
	}
}

