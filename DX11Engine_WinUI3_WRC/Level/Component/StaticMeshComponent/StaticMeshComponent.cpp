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
			//�ܺ� ���ڸ� �޾Ƽ� �ٸ� ������ StaticMesh�� ����� �ű⿡ ���缭 �̸������ϱ�
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

