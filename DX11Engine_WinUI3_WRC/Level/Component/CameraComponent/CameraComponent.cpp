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
			//�ܺ� ���ڸ� �޾Ƽ� �ٸ� ������ StaticMesh�� ����� �ű⿡ ���缭 �̸������ϱ�
			}

		void CameraComponent::Init()
		{
		}

		void CameraComponent::Tick(float elapsedTime)
		{

		}
	}
}

