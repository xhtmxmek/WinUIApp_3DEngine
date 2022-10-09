#include "EngineMinimal.h"
#include "Actor.h"
#include "Level/Component/ComponentBase/ComponentBase.h"
#include "Level/Level.h"
#include "Level/World.h"

namespace Engine
{
    namespace Level
    {        
        SharedPointer<World> Actor::GetWorld()
        {
            return SLevel::GetInstance().GetWorld();
        }


        std::shared_ptr<Component::ComponentBase> Actor::CreateComponent(const String& className, const String& instanceName)
        {            
            //런타임 클래스의 클래스명 집어넣기            
            auto iter = Components().find(className().c_str());
            if (iter == Components().end())
            {
                //new component의 포인터와 component의 타입(drawable인지, 뭐인지...를) 리턴해서 월드에 넣어주거나, 최초에 템플릿으로부터 받은 이넘타입을 월드에 넣어주기.                 
                Component::ComponentBase* runtimeComponent = (Component::ComponentBase*)RuntimeContext::New(className(), instanceName());
                std::shared_ptr<Component::ComponentBase> ptr(runtimeComponent);
                Components().insert(std::make_pair(className().c_str(), ptr));
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

