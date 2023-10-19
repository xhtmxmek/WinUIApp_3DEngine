#include "pch.h"
#include "ComponentInfo.h"
#include "TransformProperty.h"
#include "EngineCore.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "ComponentInfo.g.cpp"


namespace winrt::Editor::implementation
{
    ComponentInfo::ComponentInfo(hstring const& name)
        :name_(name),
        transform_(L"Transform"), 
        staticMesh_(L"StaticMesh"),
        rendering_(L"Rendering")
    {
    }

    void ComponentInfo::UpdateComponentDetail(hstring ownwerActorName, hstring componentName)
    {
        auto engine = Engine::GetRenderingEngine();
        auto nativeActor = weak_ptr<Engine::Level::Actor>(engine->GetActor(winrt::to_string(ownwerActorName)));
        if (nativeActor.lock() == nullptr)
            return;

        if (nativeActor.expired())
            return;

        auto nativeComponent = nativeActor.lock()->GetComponentByName(winrt::to_string(componentName));
        if (nativeComponent == nullptr)
            return;
                
        Vector3f compPos = nativeComponent->GetComponentTransform().GetPosition();
        Vector3Single fPos(compPos.x, compPos.y, compPos.z);
        transform_.Position(fPos);
        
        //native의 Type을 판별하여 Property 생성하여 properties에 넣기
    }

    hstring ComponentInfo::Name()
    {
        return name_;
    }

    void ComponentInfo::Name(hstring const& value)
    {
        if (name_ != value)
        {
            name_ = value;                        
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    Windows::Foundation::Collections::IObservableVector<winrt::Editor::PropertyBase> ComponentInfo::Properties()
    {
        return properties_;
    }

    winrt::Editor::StaticMeshProperty ComponentInfo::StaticMesh()
    {
        return staticMesh_;
    }

    winrt::Editor::TransformProperty ComponentInfo::Transform()
    {
        return transform_;
    }

    winrt::Editor::RenderingProperty ComponentInfo::Rendering()
    {
        return rendering_;
    }
}
