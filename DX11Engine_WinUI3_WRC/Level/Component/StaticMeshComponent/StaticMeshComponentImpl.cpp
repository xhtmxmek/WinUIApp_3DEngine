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

		void StaticMeshComponentImpl::Draw()
		{
		}
	}
}


