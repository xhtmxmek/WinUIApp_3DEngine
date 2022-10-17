#include "EngineMinimal.h"
#include "StaticMeshComponent.h"
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
		}

		StaticMeshComponent::~StaticMeshComponent()
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
			auto size = DX::DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
			Matrix view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),
				Vector3::Zero, Vector3::UnitY);
			Matrix proj = Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PI / 4.f,
				float(size.Width) / float(size.Height), 0.1f, 10.f);

			StaticMeshShape->Draw(GetComponentTransform().GetWorld(), view, proj);
		}
	}
}

