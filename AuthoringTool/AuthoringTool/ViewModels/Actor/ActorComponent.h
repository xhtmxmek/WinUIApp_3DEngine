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
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:        
        Windows::Foundation::Collections::IObservableVector<AuthoringTool::ActorProperty> _properties;
        winrt::hstring _name;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChanged;

    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent, implementation::ActorComponent>
    {
    };
}
