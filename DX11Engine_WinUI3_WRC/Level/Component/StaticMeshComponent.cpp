#include "EngineMinimal.h"
#include "StaticMeshComponent.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Level
	{
		StaticMeshComponent::StaticMeshComponent()
			:StaticMeshShape(nullptr)
		{		
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

