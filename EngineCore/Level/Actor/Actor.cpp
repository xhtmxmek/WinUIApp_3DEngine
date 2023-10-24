#include "pch.h"
#include "Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Level/Level.h"
#include "Level/World.h"

namespace Engine
{
    namespace Level
    {        
        shared_ptr<World> Actor::GetWorld()
        {
            return SLevel::GetWorld();
        }

        std::shared_ptr<Component::ComponentBase> Actor::CreateComponent(const string& className, const string& instanceName)
        {            
            //런타임 클래스의 클래스명 집어넣기            
            auto iter = components_.find(className.c_str());
            if (iter == components_.end())
            {
                //new component의 포인터와 component의 타입(drawable인지, 뭐인지...를) 리턴해서 월드에 넣어주거나, 최초에 템플릿으로부터 받은 이넘타입을 월드에 넣어주기.                 
                Component::ComponentBase* runtimeComponent = (Component::ComponentBase*)RuntimeContext::New(className, instanceName);
                runtimeComponent->ImplClassName(className);
                std::shared_ptr<Component::ComponentBase> ptr(runtimeComponent);
                components_.insert(std::make_pair(instanceName.c_str(), ptr));
                componentNames_.push_back(instanceName);
                ptr->Init();
                return ptr;
            }
            else
                return nullptr;
        }

        //TransformGroup const& Actor::GetTransform()
        //{
        //    return (RootComponent ? RootComponent->GetComponentTransform() : TransformGroup::Identity);
        //}
    }
}

