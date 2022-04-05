#include "pch.h"
#include "StaticMeshComponent.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
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

		void StaticMeshComponent::Update(float elapsedTime)
		{

		}

		void StaticMeshComponent::Draw()
		{
			StaticMeshShape;
		}
	}
}

