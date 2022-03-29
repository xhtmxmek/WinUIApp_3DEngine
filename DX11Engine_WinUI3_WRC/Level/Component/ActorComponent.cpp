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
	}
}

