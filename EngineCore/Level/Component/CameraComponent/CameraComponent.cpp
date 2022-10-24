#include "pch.h"
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
			}

		void CameraComponent::Init()
		{
		}

		void CameraComponent::Tick(float elapsedTime)
		{
			//엔진에서 입력을 매프레임마다 업데이트함
			//여기서 엔진 입력에 따라서 카메라 Transform 값을 처리
			/*
			* 우클릭 상태에서 마우스 움직임 : 카메라 회전
			* 우클릭 상태에서 WSAD : 카메라 이동
			* 상수 버퍼 업데이트.
			*/
			//						
		}
	}
}

