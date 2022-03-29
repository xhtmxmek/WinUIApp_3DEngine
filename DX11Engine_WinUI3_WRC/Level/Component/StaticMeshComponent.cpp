#include "pch.h"
#include "StaticMeshComponent.h"

namespace Engine
{
	namespace Component
	{
		StaticMeshComponent::StaticMeshComponent()
			:StaticMeshShape(nullptr)
		{		
		}
		void StaticMeshComponent::Init()
		{
			StaticMeshShape = DirectX::GeometricPrimitive::CreateSphere(context);
		}
		void StaticMeshComponent::Update(float elapsedTime)
		{
		}
		void StaticMeshComponent::Draw()
		{
			StaticMeshShape;
		}
	}
}

