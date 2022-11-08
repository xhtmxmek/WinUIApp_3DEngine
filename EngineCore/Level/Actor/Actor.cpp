#include "pch.h"
#include "Actor.h"
#include "Level/Component/ComponentBase/ComponentBase.h"
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
            //��Ÿ�� Ŭ������ Ŭ������ ����ֱ�            
            auto iter = components_.find(className.c_str());
            if (iter == components_.end())
            {
                //new component�� �����Ϳ� component�� Ÿ��(drawable����, ������...��) �����ؼ� ���忡 �־��ְų�, ���ʿ� ���ø����κ��� ���� �̳�Ÿ���� ���忡 �־��ֱ�.                 
                Component::ComponentBase* runtimeComponent = (Component::ComponentBase*)RuntimeContext::New(className, instanceName);
                std::shared_ptr<Component::ComponentBase> ptr(runtimeComponent);
                components_.insert(std::make_pair(className.c_str(), ptr));
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

