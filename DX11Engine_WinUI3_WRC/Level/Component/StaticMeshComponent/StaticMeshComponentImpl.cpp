#include "EngineMinimal.h"
#include "StaticMeshComponentImpl.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		void StaticMeshComponentImpl::Init()
		{
			//이넘을 넘겨주어 이넘을로 구분하여 만들기
			auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			StaticMeshShape = DirectX::GeometricPrimitive::CreateSphere(context);			
		}

		void StaticMeshComponentImpl::Tick(float elapsedTime)
		{
		}

		void StaticMeshComponentImpl::Draw(const Engine::Math::TransformGroup& transform)
		{						
			auto size = DX::DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
			Matrix view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),
				Vector3::Zero, Vector3::UnitY);
			Matrix proj = Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PI / 4.f,
				float(size.Width) / float(size.Height), 0.1f, 10.f);

			StaticMeshShape->Draw(transform.GetWorld(), view, proj);
			//StaticMeshShape->Draw()
		}
	}
}


