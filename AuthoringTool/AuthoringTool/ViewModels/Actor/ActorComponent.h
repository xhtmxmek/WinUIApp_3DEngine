#pragma once
#include "ActorComponent.g.h"
#include "ActorProperty.h"

namespace winrt::AuthoringTool::implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent>
    {
        ActorComponent() = delete;

        ActorComponent(hstring const& name);
        hstring Name();        
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorProperty> Properties();
    private:        
        Windows::Foundation::Collections::IObservableVector<AuthoringTool::ActorProperty> _properties;
        winrt::hstring _name;
    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent, implementation::ActorComponent>
    {
    };
}
