#include "pch.h"
#include "ActorDetail.h"
#include "Level/Actor/Actor.h"
#include "ComponentInfo.h"
//#include "TransformProperty.h"
//#include "RenderingProperty.h"
#include "EngineCore.h"
#include "Component/ComponentBase/ComponentBase.h" 


#include "ActorDetail.g.cpp"

namespace winrt::Editor::implementation
{
    ActorDetail::ActorDetail(hstring const& name)
        :name_(name)
    {
        componentInfos_ = winrt::single_threaded_observable_vector<Editor::ComponentInfo>();
        //selectedComponent_ = winrt::make<Editor::implementation::ComponentInfo>(L"");

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
            //PropertyChanged([this] {
            //    *this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" };
            //    });
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

    void ActorDetail::UpdateActorDeail(hstring actorName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
    {
        if (visible_ == Microsoft::UI::Xaml::Visibility::Visible)
            return;

        auto engine = Engine::GetRenderingEngine();
        nativeActor_ = weak_ptr<Engine::Level::Actor>(engine->GetActor(winrt::to_string(actorName)));
        if (nativeActor_.lock() == nullptr)
            return;

        for (int compIndex = 0; compIndex < nativeActor_.lock()->NumComponent(); compIndex++)
        {
            //auto nativeComponent = nativeActor->GetComponentByIndex(compIndex);
            auto nativeComponent = nativeActor_.lock()->GetComponentByIndex(compIndex);
            if (nativeComponent == nullptr)
                continue;

            auto componentLabel = winrt::to_hstring(nativeComponent->Name() + " ("
                + nativeComponent->ImplClassName() + ")");
            winrt::Editor::ComponentInfo componentProxy(winrt::to_hstring(componentLabel));

            ComponentInfos().Append(componentProxy);
            Name(actorName);
            Visible(Microsoft::UI::Xaml::Visibility::Visible);
        }

        auto RootComponent = nativeActor_.lock()->GetRootComponent();        
        if (RootComponent)
        {
            UpdateSelectedComponent(winrt::to_hstring(RootComponent->Name()), detailPanel);
        }
    }

    void ActorDetail::UpdateSelectedComponent(hstring componentName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
    {
        selectedComponent_ = winrt::make<Editor::implementation::ComponentInfo>(L"");
        //SelectedComponent의 Transform도 업데이트해야됨
        selectedComponent_.UpdateComponentDetail(name_, componentName, detailPanel);

    }

    void ActorDetail::Clear(Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
    {
		ComponentInfos().Clear();
		Name().clear();
        detailPanel.Children().Clear();
        selectedComponent_ = nullptr;
		Visible(Microsoft::UI::Xaml::Visibility::Collapsed);
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
}