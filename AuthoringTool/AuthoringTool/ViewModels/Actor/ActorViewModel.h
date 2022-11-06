#pragma once
#include "ActorViewModel.g.h"
#include "ActorComponent.h"

namespace EngineInterface_WRC
{
    struct ActorProxy;
}

namespace winrt::AuthoringTool::implementation
{
    struct ActorViewModel : ActorViewModelT<ActorViewModel>
    {
        ActorViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorComponent> Components();
        hstring Name();
        void Name(hstring const& value);
        void SetActor(EngineInterface_WRC::ActorProxy const& actor);
    private:
        Windows::Foundation::Collections::IObservableVector<AuthoringTool::ActorComponent> _components;
        winrt::hstring _name;
    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorViewModel : ActorViewModelT<ActorViewModel, implementation::ActorViewModel>
    {
    };
}
