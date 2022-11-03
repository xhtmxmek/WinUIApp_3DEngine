#pragma once
#include "ActorProperty.g.h"

namespace winrt::AuthoringTool::implementation
{
    struct ActorProperty : ActorPropertyT<ActorProperty>
    {
        ActorProperty() = default;

        ActorProperty(hstring const& name);
        hstring Name();
        void Name(hstring const& value);
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::hstring _name;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChanged;
    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorProperty : ActorPropertyT<ActorProperty, implementation::ActorProperty>
    {
    };
}
