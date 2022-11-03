#pragma once
#include "ActorViewModel.g.h"

namespace winrt::AuthoringTool::implementation
{
    struct ActorViewModel : ActorViewModelT<ActorViewModel>
    {
        ActorViewModel() = default;

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorComponent> Components();
        hstring Name();
        void Name(hstring const& value);
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
