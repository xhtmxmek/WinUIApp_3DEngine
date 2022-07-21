#include "EngineMinimal.h"
#include "ComponentBaseImpl.h"

namespace Engine
{
	namespace Component
	{
		ComponentBaseImpl::ComponentBaseImpl(const std::string& name, SceneComponentType type)
			:Name(name),
			Type(type),
			//Parent(nullptr),
			Enable(false)
		{
		}

		void ComponentBaseImpl::SetPosition(DirectX::SimpleMath::Vector3 const& pos)
		{
		}

		void ComponentBaseImpl::SetScale(DirectX::SimpleMath::Vector3 const& scale)
		{
		}

		void ComponentBaseImpl::SetRotation(DirectX::SimpleMath::Vector3 const& rot)
		{
			//Transform.
		}

		DirectX::SimpleMath::Vector3 ComponentBaseImpl::GetRotation()
		{
			return Vector3(1,1,1);
		}

		void ComponentBaseImpl::UpdateComponentTransform(const Level::TransformGroup* parent)
		{

		}
	}
}