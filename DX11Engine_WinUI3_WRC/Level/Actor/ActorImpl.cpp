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
                //new component�� �����Ϳ� component�� Ÿ��(drawable����, ������...��) �����ؼ� ���忡 �־��ְų�, ���ʿ� ���ø����κ��� ���� �̳�Ÿ���� ���忡 �־��ֱ�. 
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
        //    // // O: ���⿡ return ���� �����մϴ�.
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
