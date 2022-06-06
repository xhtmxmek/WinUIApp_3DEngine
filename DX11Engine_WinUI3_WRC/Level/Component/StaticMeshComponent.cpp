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
			//�ܺ� ���ڸ� �޾Ƽ� �ٸ� ������ StaticMesh�� ����� �ű⿡ ���缭 �̸������ϱ�
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

