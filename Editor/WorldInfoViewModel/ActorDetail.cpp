#include "pch.h"
#include "ActorDetail.h"
#include "Level/Actor/Actor.h"
#include "ComponentInfo.h"
#include "TransformProperty.h"
#include "RenderingProperty.h"
#include "EngineCore.h"
#include "Component/ComponentBase/ComponentBase.h" 


#include "ActorDetail.g.cpp"

namespace winrt::Editor::implementation
{
    ActorDetail::ActorDetail(hstring const& name)
        :name_(name)
    {
        componentInfos_ = winrt::single_threaded_observable_vector<Editor::ComponentInfo>();
        selectedComponent_ = winrt::make<Editor::implementation::ComponentInfo>(L"");

    }

    hstring ActorDetail::Name()
    {
        return name_;
    }

    void ActorDetail::Name(hstring const& value)
    {
        if (name_ != value)
        {
            name_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> ActorDetail::ComponentInfos()
    {
        return componentInfos_;
    }

    winrt::Editor::ComponentInfo ActorDetail::SelectedComponent()
    {
        return selectedComponent_;
    }

    void ActorDetail::UpdateSelectedComponent(hstring componentName)
    {
        auto engine = Engine::GetRenderingEngine();
        auto nativeActor = engine->GetActor(winrt::to_string(name_));
        if (nativeActor != nullptr)
            return;

        auto nativeComponent = nativeActor->GetComponentByName(winrt::to_string(componentName));
        if (nativeComponent != nullptr)
            return;

        winrt::Editor::TransformProperty transform = { nullptr };
        transform = winrt::make<Editor::implementation::TransformProperty>(L"Transform");
        Vector3f compPos = nativeComponent->GetComponentTransform().GetPosition();
        Vector3Single fPos(compPos.x, compPos.y, compPos.z);
        transform.Position(fPos);

        selectedComponent_.Transform(transform);
    }

    winrt::Microsoft::UI::Xaml::Visibility ActorDetail::Visible()
    {
        return visible_;
    }

    void ActorDetail::Visible(winrt::Microsoft::UI::Xaml::Visibility const& value)
    {
        if (visible_ != value)
        {
            visible_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Visible" });
        }
    }

    winrt::event_token ActorDetail::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }
    void ActorDetail::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}