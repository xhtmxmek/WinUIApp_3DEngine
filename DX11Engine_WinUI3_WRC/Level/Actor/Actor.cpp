#include "EngineMinimal.h"
//#include "Level/Component/ComponentBase.h"
//#include "Level/Component/ComponentTypes.h"
//#include "Level/Component/TransformGroup.h"
#include "ActorImpl.h"
#include "Actor.h"
#include "Level/Component/ComponentBase.h"

namespace Engine
{
    namespace Level
    {
        Actor::Actor(const std::string& name)
        {
            pImpl = new ActorImpl(name);
        }

        Actor::~Actor()
        {
            delete pImpl;
        }

        void Actor::SetRootComponent(Component::ComponentBase* component)
        {            
            pImpl->SetRootComponent(component);
        }

        std::unique_ptr<World>& Actor::GetWorld()
        {         
            return pImpl->GetWorld();
        }

        std::shared_ptr<Component::ComponentBase> Actor::CreateComponent(const std::string& className, const std::string& instanceName)
        {            
            //��Ÿ�� Ŭ������ Ŭ������ ����ֱ�
            return pImpl->CreateComponent(className, instanceName);
        }

        std::shared_ptr<Component::ComponentBase> Actor::GetComponentByName(const std::string& name)
        {            
            return pImpl->GetActorComponentByName(name);
        }

        //TransformGroup const& Actor::GetTransform()
        //{
        //    return (RootComponent ? RootComponent->GetComponentTransform() : TransformGroup::Identity);
        //}
    }
}

