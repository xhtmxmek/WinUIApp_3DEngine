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

		void ComponentBaseImpl::UpdateComponentTransform(const TransformGroup* parent)
		{
			//std::for_each(Child.begin(), Child.end(),
			//	[this](std::shared_ptr<ComponentBase>& component) {
			//		ComponentBase* child = component.get();
			//		if (child)
			//			child->UpdateComponentTransform(&Transform);
			//	});
		}
	}
}