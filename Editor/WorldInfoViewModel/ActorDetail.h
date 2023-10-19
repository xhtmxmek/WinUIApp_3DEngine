#pragma once
#include "ObservableObject.h"
#include "ActorDetail.g.h"

namespace Engine
{
    namespace Level
    {
        class Actor;
    }
}

namespace winrt::Editor::implementation
{    
    struct ActorDetail : ActorDetailT<ActorDetail, Editor::implementation::ObservableObject>
    {
        ActorDetail() = delete;

        ActorDetail(hstring const& name);


        void UpdateActorDeail(hstring actorName);        
        void UpdateSelectedComponent(hstring componentName);
        void Clear();


        hstring Name();
        void Name(hstring const& value);

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> ComponentInfos();
        winrt::Editor::ComponentInfo SelectedComponent();        

        winrt::Microsoft::UI::Xaml::Visibility Visible();
        void Visible(winrt::Microsoft::UI::Xaml::Visibility const& value);

    private:
        hstring name_;
        winrt::Microsoft::UI::Xaml::Visibility visible_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> componentInfos_;
        winrt::Editor::ComponentInfo selectedComponent_ = { nullptr };
        std::weak_ptr<Engine::Level::Actor> nativeActor_;

    };
}
namespace winrt::Editor::factory_implementation
{
    struct ActorDetail : ActorDetailT<ActorDetail, implementation::ActorDetail>
    {
    };
}
