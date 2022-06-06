#include "EngineMinimal.h"
#include "StaticMeshComponent.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		StaticMeshComponent::StaticMeshComponent()
			:DrawableComponent("StaticMesh"),
			StaticMeshShape(nullptr)
		{
			//외부 인자를 받아서 다른 종류의 StaticMesh를 만들면 거기에 맞춰서 이름세팅하기
		}

		void StaticMeshComponent::Init()
		{
			auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			StaticMeshShape = DirectX::GeometricPrimitive::CreateSphere(context);
		}

		void StaticMeshComponent::Tick(float elapsedTime)
		{

		}

		void StaticMeshComponent::Draw()
		{
			//StaticMeshShape;
		}
	}
}

