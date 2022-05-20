#include "pch.h"
#include "Level/Component/ComponentBase.h"
#include "Level/Component/ComponentTypes.h"
#include "Level/Component/TransformGroup.h"
#include "Actor.h"

namespace Engine
{
    namespace Level
    {
        Component::TransformGroup const& Actor::GetTransform()
        {
            return (RootComponent ? RootComponent->GetComponentTransform() : Component::TransformGroup::Identity);
        }
    }
}

