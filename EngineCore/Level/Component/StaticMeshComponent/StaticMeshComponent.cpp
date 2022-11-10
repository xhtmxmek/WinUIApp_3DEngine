#include "pch.h"
#include "StaticMeshComponent.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(StaticMeshComponent)

		StaticMeshComponent::StaticMeshComponent(const std::string& name)
			:DrawableComponent(name),
			staticMeshShape_(nullptr)
		{						
		}

		StaticMeshComponent::~StaticMeshComponent()
		{			
		}

		void StaticMeshComponent::Init()
		{
			auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			staticMeshShape_ = DirectX::GeometricPrimitive::CreateSphere(context);		
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

			//요거는... 바꾸자. 직접 파이프라인에 세팅해서 렌더링하는걸로
			DirectX::SimpleMath::Matrix(&GetComponentTransform().GetWorldMatrix()._11);
			staticMeshShape_->Draw(DirectX::SimpleMath::Matrix(&GetComponentTransform().GetWorldMatrix()._11), view, proj);
		}
	}
}

