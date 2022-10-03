#include "EngineMinimal.h"
#include "StaticMeshComponent.h"
#include "StaticMeshComponentImpl.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(StaticMeshComponent)

		StaticMeshComponent::StaticMeshComponent(const std::string& name)
			:DrawableComponent(name)
			//StaticMeshShape(nullptr)
		{
			//외부 인자를 받아서 다른 종류의 StaticMesh를 만들면 거기에 맞춰서 이름세팅하기
			pImpl = new StaticMeshComponentImpl();
		}

		StaticMeshComponent::~StaticMeshComponent()
		{
			delete pImpl;
		}

		void StaticMeshComponent::Init()
		{
			pImpl->Init();
		}

		void StaticMeshComponent::Tick(float elapsedTime)
		{
			pImpl->Tick(elapsedTime);
		}

		void StaticMeshComponent::Draw()
		{						
			pImpl->Draw(GetComponentTransform());
		}
	}
}

