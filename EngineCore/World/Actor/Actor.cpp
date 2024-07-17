#include "pch.h"
#include "Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Level/Level.h"
#include "Level/World.h"

namespace Engine
{
    namespace World
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

