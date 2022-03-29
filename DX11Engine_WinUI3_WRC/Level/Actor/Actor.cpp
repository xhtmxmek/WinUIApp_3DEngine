#include "pch.h"
#include "Level/Component/ActorComponent.h"
#include "Level/Component/ComponentName.h"
#include "Level/Component/TransformGroup.h"
#include "Actor.h"

namespace Engine
{
    namespace Level
    {
        void Actor::Init()
        {
            //TransformGroup�� ������ setting�Ǿ����
            Components.insert_or_assign(Component::ActorComponentType::TransformGroup, std::shared_ptr<Component::TransformGroup>(new Component::TransformGroup()));
        }
    }
}

