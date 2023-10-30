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
	namespace Component
	{
		RUNTIME_CLASS_IMPL(CameraComponent);

		CameraComponent::CameraComponent(const std::string& name)
			:ComponentBase(name, SceneComponentType::Camera)
		{
			cameraMoveSwitch_ = false;
		}

		void CameraComponent::Init()
		{
			keyMap_.insert(make_pair(VirtualKey::W, [this]()
				{
					MoveFoward();
				}));

			keyMap_.insert(make_pair(VirtualKey::S, [this]()
				{
					MoveFoward(-1.f);
				}));

			keyMap_.insert(make_pair(VirtualKey::A, [this]()
				{
					MoveRight(-1.f);
				}));

			keyMap_.insert(make_pair(VirtualKey::D, [this]()
				{
					MoveRight();
				}));
		}

		void CameraComponent::Tick(float elapsedTime)
		{
			ProcessInput();
			UpdateConstantBuffer();
		}
		void CameraComponent::ProcessInput()
		{
			for (auto iter : keyMap_)
			{
				auto KeyValue = iter.first;
				if (Input::InputManager::GetInstance().GetKeyboardState(KeyValue))
				{
					auto bindFunc = iter.second;
					bindFunc();
				}
			}

			LookAt();
		}
		void CameraComponent::MoveFoward(float DirectionFactor)
		{
		}
		void CameraComponent::MoveRight(float DirectionFactor)
		{
		}
		void CameraComponent::LookAt()
		{
			//마우스 우클릭시
			if (Input::InputManager::GetInstance().GetMouseState(PointerButton::RightButton))
			{
				cameraMoveSwitch_ = true;
			}
			auto mousePos = Input::InputManager::GetInstance().GetMousePos();
			//if ()
			//if (rButtonState.delta_)
			//{
			//	if (cameraMoveLock)
			//	{
			//		Math::Vector3 mouseDelta = InputCenter::GetInstance()->GetMouseMove();
			//		int screenWidth = 0;
			//		int screenHeight = 0;
			//		DXUtility::GetInstance()->GetDeviceWidthHeight(screenWidth, screenHeight);


			//		float deltaX = mouseDelta.x / (float)screenWidth;
			//		float deltaY = mouseDelta.y / (float)screenHeight;

			//		//float deltaX = mouseDelta.x * 0.001f;
			//		//float deltaY = mouseDelta.y * 0.001f;


			//		//Matrix rMat = Matrix::MatrixRotationAxis(Right, deltaY * 0.4f);
			//		//Look = Matrix::TransformCoord(Vector3(0, 0, 1), rMat);
			//		//Look.Normalize();

			//		//Matrix yRotMat = Matrix::MatrixRotationAxis(Vector3(0, 1, 0), deltaX);
			//		//Matrix yRotMat = Matrix::MatrixRotationY(m_fYaw);
			//		//Right = Matrix::TransformCoord(Vector3(1, 0, 0), yRotMat);
			//		//Up = Matrix::TransformCoord(Up, yRotMat);
			//		//Up.Normalize();


			//		//Pos += moveLeftRight * camRight;
			//		//camPosition += moveBackForward * camForward;

			//		//Foward = Matrix::TransformCoord(Vector3(0, 0, 1), yRotMat);

			//		//x축 회전

			//		if (deltaY != 0)
			//		{
			//			Matrix xRotMat = Matrix::MatrixRotationAxis(Right, deltaY);
			//			Up = Matrix::TransformNormal(Up, xRotMat);
			//			Look = Matrix::TransformNormal(Look, xRotMat);
			//		}

			//		//y축 회전
			//		if (deltaX != 0)
			//		{
			//			Matrix yRotMat = Matrix::MatrixRotationY(deltaX);

			//			Right = Matrix::TransformNormal(Right, yRotMat);
			//			Up = Matrix::TransformNormal(Up, yRotMat);
			//			Look = Matrix::TransformNormal(Look, yRotMat);
			//		}


			//	}


			//}
			//if (InputCenter::GetInstance()->IsButtonUp(MOUSE_RIGHT))
			//{
			//	cameraMoveLock = false;
			//}
		}
		void CameraComponent::UpdateConstantBuffer()
		{
			//ID3D11Buffer* cameraBuff;
			//cameraBuff = *ConstantBufferManager::GetInstance().GetBuffer(ConstantBufferManager::ConstBufferType::perCamera);
			Renderer::GraphicsLibrary::ConstantBufferManager::CameraConstBuffFormat camBuffFormat;
			camBuffFormat.View = viewMatrix_;
			//camBuffFormat.Proj = 
			//camBuffFormat.CamPos = Math::Vector4(Pos.x, Pos.y, Pos.z, 0);
			//camBuffFormat.minMaxDistance = Math::Vector4(0.01, 4.1, 0, 0);
			//camBuffFormat.minMaxLOD = Math::Vector4(1, 6, 0, 0);
			////cam
			//D3D11_MAPPED_SUBRESOURCE camMappedResource;
			//DXUtility::GetInstance()->GetDeviceContext()->Map(cameraBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &camMappedResource);
			//memcpy(camMappedResource.pData, &camBuffFormat, sizeof(ConstantBufferManager::CameraConstBuffFormat));
			//DXUtility::GetInstance()->GetDeviceContext()->Unmap(cameraBuff, 0);
		}
	}
}

