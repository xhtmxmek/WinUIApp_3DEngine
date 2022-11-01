#pragma once
#include "ActorComponent.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent>
    {
        ActorComponent() = default;

        ActorComponent(hstring const& title);
        hstring Title();
        void Title(hstring const& value);
        winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::hstring m_title;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent, implementation::ActorComponent>
    {
    };
}
