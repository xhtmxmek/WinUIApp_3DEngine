#pragma once
#include "ComponentPropertyProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ComponentPropertyProxy : ComponentPropertyProxyT<ComponentPropertyProxy>
    {
        ComponentPropertyProxy() = default;

        ComponentPropertyProxy(hstring const& name);
        hstring Name();
        winrt::Microsoft::UI::Xaml::UIElement MappedControl();
        void MappedControl(winrt::Microsoft::UI::Xaml::UIElement const& value);
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;
        winrt::Microsoft::UI::Xaml::UIElement mappedControl_{ nullptr };
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ComponentPropertyProxy : ComponentPropertyProxyT<ComponentPropertyProxy, implementation::ComponentPropertyProxy>
    {
    };
}
