#include "EngineMinimal.h"
#include "Level/Component/ComponentBase.h"
#include "Level/Component/ComponentTypes.h"
#include "Common/RuntimeContext.h"
//#include "Level/Component/TransformGroup.h"
#include "ActorImpl.h"

namespace Engine
{
    namespace Level
    {
        std::shared_ptr<Component::ComponentBase> ActorImpl::CreateComponent(const std::string& className, const std::string& instanceName)
        {
            auto iter = Components.find(className);
            if (iter == Components.end())
            {
                Component::ComponentBase* runtimeComponent = (Component::ComponentBase*)RuntimeContext::New(className, instanceName);
                std::shared_ptr<Component::ComponentBase> ptr(runtimeComponent);
                Components.insert(std::make_pair(className, ptr));
                return ptr;                
            }
            else
                return nullptr;
        }
        //void ActorImpl::SetRootComponent(Component::ComponentBase* component)
        //{
        //    RootComponent = component;    
        //}
        //TransformGroup const& Actor::GetTransform()
        //{
        //    return (RootComponent ? RootComponent->GetComponentTransform() : TransformGroup::Identity);
        //}
    }
}
