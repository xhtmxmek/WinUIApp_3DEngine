#include "EngineMinimal.h"
#include "Level/Component/ComponentBase.h"
#include "Level/Component/ComponentTypes.h"
#include "Level/Component/TransformGroup.h"
#include "Actor.h"

namespace Engine
{
    namespace Level
    {
        TransformGroup const& Actor::GetTransform()
        {
            return (RootComponent ? RootComponent->GetComponentTransform() : TransformGroup::Identity);
        }
    }
}

