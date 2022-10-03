#include "EngineMinimal.h"
#include "Level/Component/ComponentBase/ComponentBase.h"
#include "Level/Component/ComponentTypes.h"
#include "Common/RuntimeContext.h"
//#include "Level/Component/TransformGroup.h"
#include "ActorImpl.h"
#include "Level/Component/ComponentLinker.h"
#include "Level/Level.h"
#include "Level/World.h"

namespace Engine
{
    namespace Level
    {
        std::shared_ptr<Component::ComponentBase> ActorImpl::CreateComponent(const std::string& className, const std::string& instanceName)
        {
            auto iter = Components.find(className);
            if (iter == Components.end())
            {
                //new component의 포인터와 component의 타입(drawable인지, 뭐인지...를) 리턴해서 월드에 넣어주거나, 최초에 템플릿으로부터 받은 이넘타입을 월드에 넣어주기. 
                Component::ComponentBase* runtimeComponent = (Component::ComponentBase*)RuntimeContext::New(className, instanceName);
                std::shared_ptr<Component::ComponentBase> ptr(runtimeComponent);
                Components.insert(std::make_pair(className, ptr));
                ptr->Init();
                return ptr;                
            }
            else
                return nullptr;
        }

        std::shared_ptr<World> ActorImpl::GetWorld()
        {
            return SLevel::GetInstance().GetWorld();
        }
        //SLevel& ActorImpl::GetLevel()
        //{
        //    return 
        //    // // O: 여기에 return 문을 삽입합니다.
        //}
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
