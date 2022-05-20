#include "pch.h"
#include "ComponentBase.h"
namespace Engine
{		
	void ComponentBase::SetPosition(Vector3 const& pos)
	{
		Transform.SetPosition(pos);
	}
	void ComponentBase::SetScale(Vector3 const& scale)
	{
		Transform.SetScale(scale);
	}
	void ComponentBase::SetRotation(Vector3 const& rot)
	{
		Transform.SetRotation(rot);
	}
	void ComponentBase::UpdateComponentTransform(const TransformGroup* parent)
	{
		std::for_each(Child.begin(), Child.end(),
			[](std::shared_ptr<ComponentBase>& component) {
				ComponentBase* child = component.get();
				if (child)
					child->UpdateComponentTransform(&child->GetComponentTransform());
			});
	}	
}

