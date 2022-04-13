#include "pch.h"
#include "ActorComponent.h"
namespace Engine
{
	namespace Component
	{
		void ActorComponent::SetPosition(Vector3 const& pos)
		{
			Transform.SetPosition(pos);
		}
		void ActorComponent::SetScale(Vector3 const& scale)
		{
			Transform.SetScale(scale);
		}
		void ActorComponent::SetRotation(Vector3 const& rot)
		{
			Transform.SetRotation(rot);
		}
		void ActorComponent::UpdateComponentTransform(const TransformGroup* parent)
		{
			std::for_each(Child.begin(), Child.end(),
				[](std::shared_ptr<ActorComponent>& component) {
					ActorComponent* child = component.get();
					if (child)
						child->UpdateComponentTransform(&child->GetComponentTransform());
				});
		}
	}
}

