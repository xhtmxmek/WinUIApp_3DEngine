#include "EngineMinimal.h"
#include "StaticMeshComponentImpl.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		void StaticMeshComponentImpl::Init()
		{
			//�̳��� �Ѱ��־� �̳����� �����Ͽ� �����
			auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			StaticMeshShape = DirectX::GeometricPrimitive::CreateSphere(context);
		}

		void StaticMeshComponentImpl::Tick(float elapsedTime)
		{
		}

		void StaticMeshComponentImpl::Draw()
		{
		}
	}
}


