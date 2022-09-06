#include "EngineMinimal.h"
#include "CameraComponent.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(CameraComponent)

			CameraComponent::CameraComponent(const std::string& name)
			:ComponentBase(name, SceneComponentType::Camera)
			{
			//외부 인자를 받아서 다른 종류의 StaticMesh를 만들면 거기에 맞춰서 이름세팅하기
			}

		void CameraComponent::Init()
		{
		}

		void CameraComponent::Tick(float elapsedTime)
		{

		}
	}
}

