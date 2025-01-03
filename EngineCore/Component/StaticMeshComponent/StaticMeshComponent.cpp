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
			_assetDirectory(assetDirectory),
			deformable(false)
		{
			SetVisible(true);
		}

		StaticMeshComponent::~StaticMeshComponent()
		{			
		}

		void StaticMeshComponent::Init()
		{
			
			_staticMesh = make_shared<Asset::Mesh>();
			_staticMesh->Load(_assetDirectory);
			// load한 정보는 importer에 의한것. importer에서 로드한 정보를 렌더 쓰레드에서 쓸수 있게 다시 가공해야 함.
			// instancedStaticMesh가 아니라고 해도, 동일한 기하구조의 staticMeshComponent가 씬에 여러개 있다고하여 VertexBuffer를 각각 다르게 생성할 필요는 없다. deformable이 아닌이상.
			// vertexBuffer는 렌더 쓰레드의 애셋이기 떄문에, PrimitiveScene을 호출할때 MeshInfo에 담아서 보낸다.
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
			if (deformable)
			//Create Vertex Buffer
			//Create Index Buffer
			//Create Material Info
		}

		void StaticMeshComponent::PostInitialize()
		{
			AddPrimitiveToScene();
		}
	}
}

