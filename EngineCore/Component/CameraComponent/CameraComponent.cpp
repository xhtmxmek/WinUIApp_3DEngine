#include "pch.h"
#include "CameraComponent.h"
#include "Renderer/Resource/DeviceResources.h"
#include "System/KeyboardState.h"
#include "System/InputManager.h"
#include <Input/PointerButton.h>
#include <Input/VirtualKey.h>
#include "Renderer/Resource/ConstantBuffer.h"

namespace Engine
{
	using namespace Renderer;
	using namespace Renderer::RLI;

	namespace Component
	{
		RUNTIME_CLASS_IMPL(CameraComponent);

		CameraComponent::CameraComponent(const std::string& name)
			:ComponentBase(name, SceneComponentType::Camera),
			cameraMoveSwitch_(false),
			focusPoint_(0.f, 0.f, 0.f),
			upVector_(0.f, 1.f, 0.f),
			useBlur_(L"Use Blur", L"PostProcess")
		{			
			GetComponentTransform().SetPosition(Vector3f(2.f, 2.f, 2.f));
		}

		void CameraComponent::Init()
		{
			keyMap_.insert(make_pair(VirtualKey::W, [this](float elapsedTime)
				{
					MoveFoward(1.f);
				}));

			keyMap_.insert(make_pair(VirtualKey::S, [this](float elapsedTime)
				{
					MoveFoward(-1.f);
				}));

			keyMap_.insert(make_pair(VirtualKey::A, [this](float elapsedTime)
				{
					MoveRight(-1.f);
				}));

			keyMap_.insert(make_pair(VirtualKey::D, [this](float elapsedTime)
				{
					MoveRight(1.f);
				}));

			AddProperty(&useBlur_);

			useBlur_.BindChangedEvent(std::bind(
				[this](Component::PropertyBase*)
				{					
				}, std::placeholders::_1));
		}

		void CameraComponent::Tick(float elapsedTime)
		{
			ProcessInput(elapsedTime);
			UpdateConstantBuffer();
		}

		void CameraComponent::ProcessInput(float elapsedTime)
		{
			for (auto iter : keyMap_)
			{
				auto KeyValue = iter.first;
				if (Input::InputManager::GetInstance().GetKeyboardState(KeyValue))
				{
					auto bindFunc = iter.second;
					bindFunc(elapsedTime);
				}
			}

			LookAt();
		}

		void CameraComponent::MoveFoward(float directionFactor, float elapsedTime)
		{
			Vector3f foward = GetComponentTransform().GetFowardVector();
			Vector3f currentPos = GetComponentTransform().GetPosition();
			Vector3f newPos = currentPos + foward * directionFactor * elapsedTime;
			GetComponentTransform().SetPosition(newPos);
		}

		void CameraComponent::MoveRight(float directionFactor, float elapsedTime)
		{
			Vector3f right = GetComponentTransform().GetRightVector();
			Vector3f currentPos = GetComponentTransform().GetPosition();
			Vector3f newPos = currentPos + right * directionFactor * elapsedTime;
			GetComponentTransform().SetPosition(newPos);
		}

		void CameraComponent::LookAt()
		{
			//���콺 ��Ŭ����
			if (Input::InputManager::GetInstance().GetMouseState(PointerButton::RightButton))
			{
				cameraMoveSwitch_ = true;
			}

			auto mousePos = Input::InputManager::GetInstance().GetMousePos();
			Vector2f mouseDelta = Input::InputManager::GetInstance().GetMouseDelta();

			SharedTypes::Size viewportSize = DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();

			float deltaX = mouseDelta.x / (float)viewportSize.Width;
			float deltaY = mouseDelta.y / (float)viewportSize.Height;
			//ȸ�������� ������ �ʿ��ϴ�. �⺻���� ���콺�� ȭ�鸸ŭ ������������ 180���� �α�.

			float yawDegree = deltaX *= 360.f;
			float pitchDegree = deltaY *= 360.f;
			GetComponentTransform().SetRotation(Vector3f(pitchDegree, yawDegree, 0.f));

			float radianYaw = SharedTypes::ConvertToRadian(deltaX);
			float radianPitch = SharedTypes::ConvertToRadian(deltaY);			

			
			//fowardVector�� 0,0,1�� ȸ�� ��ȯ�� �����Ѱ�.
						
			//Tool Camera�� ȸ���� local �������� ����Ǿ� �ùٸ��� �� �� �ִ�.
			if (radianPitch != 0 || radianYaw != 0)
			{
				focusPoint_ *= GetComponentTransform().GetWorldMatrix();			
			}
		}
		void CameraComponent::UpdateConstantBuffer()
		{
			ConstantBufferManager::CameraConstBuffFormat camBuffFormat;
			//camBuffFormat.Proj = Matrix4x4f::look
			Vector3f pos = GetComponentTransform().GetPosition();
			camBuffFormat.CamPos = Vector4f(pos.x, pos.y, pos.z, 0.f);
			camBuffFormat.minMaxDistance = Vector4f(0.01f, 4.1f, 0.f, 0.f);
			camBuffFormat.minMaxLOD = Vector4f(1.f, 6.f, 0.f, 0.f);

			Vector3f upVector = GetComponentTransform().GetUpVector();
			XMFLOAT3 f3CamPos = XMFLOAT3(pos.x, pos.y, pos.z);
			XMFLOAT3 f3FocusPoint = XMFLOAT3(focusPoint_.x, focusPoint_.y, focusPoint_.z);			
			XMFLOAT3 f3UpVector = XMFLOAT3(upVector.x, upVector.y, upVector.z);
			XMFLOAT4X4 f4ViewMat;
			XMStoreFloat4x4(&f4ViewMat, DirectX::XMMatrixLookAtLH(XMLoadFloat3(&f3CamPos), XMLoadFloat3(&f3FocusPoint), XMLoadFloat3(&f3UpVector)));

			camBuffFormat.View = Matrix4x4f(f4ViewMat._11, f4ViewMat._12, f4ViewMat._13, f4ViewMat._14,
				f4ViewMat._21, f4ViewMat._22, f4ViewMat._23, f4ViewMat._24,
				f4ViewMat._31, f4ViewMat._32, f4ViewMat._33, f4ViewMat._34,
				f4ViewMat._41, f4ViewMat._42, f4ViewMat._43, f4ViewMat._44);

			SharedTypes::Size viewportSize = DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
			XMFLOAT4X4 f4ProjMat;
			XMStoreFloat4x4(&f4ProjMat, XMMatrixPerspectiveFovLH(XM_PIDIV4, viewportSize.Width / viewportSize.Height, 0.01f, 100.0f));

			camBuffFormat.Proj = Matrix4x4f(f4ProjMat._11, f4ProjMat._12, f4ProjMat._13, f4ProjMat._14,
				f4ProjMat._21, f4ProjMat._22, f4ProjMat._23, f4ProjMat._24,
				f4ProjMat._31, f4ProjMat._32, f4ProjMat._33, f4ProjMat._34,
				f4ProjMat._41, f4ProjMat._42, f4ProjMat._43, f4ProjMat._44);

			ConstantBufferManager::GetInstance().UpdateConstantBuffer(ConstantBufferManager::StaticConstBufferType::perCamera, &camBuffFormat, 
				sizeof(ConstantBufferManager::CameraConstBuffFormat));
		}
	}
}

