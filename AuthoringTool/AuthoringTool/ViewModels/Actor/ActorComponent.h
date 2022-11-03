#pragma once
#include "ActorComponent.g.h"

namespace winrt::AuthoringTool::implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent>
    {
        ActorComponent() = default;

        ActorComponent(hstring const& name);
        hstring Name();        
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorProperty> Properties();
    private:        
        Windows::Foundation::Collections::IObservableVector<AuthoringTool::ActorComponent> _properties;
        winrt::hstring _name;
    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent, implementation::ActorComponent>
    {
    };
}
