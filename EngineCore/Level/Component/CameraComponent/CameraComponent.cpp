#include "pch.h"
#include "CameraComponent.h"
#include "Common/DeviceResources.h"
#include "System/InputManager.h"

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
			
			Get
			// 						
			//���⼭ ���� �Է¿� ���� ī�޶� Transform ���� ó��
			/*
			* ��Ŭ�� ���¿��� ���콺 ������ : ī�޶� ȸ��
			* ��Ŭ�� ���¿��� WSAD : ī�޶� �̵�
			* ��� ���� ������Ʈ.
			*/
			//						
		}		
	}
}

