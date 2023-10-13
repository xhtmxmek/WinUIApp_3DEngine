#pragma once
#include "RenderingProperty.g.h"


namespace winrt::Editor::implementation
{
    struct RenderingProperty : RenderingPropertyT<RenderingProperty>
    {
        RenderingProperty() = delete;

        RenderingProperty(hstring const& name);
        hstring Name();
        bool Visible();
        void Visible(bool value);
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        bool visible_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;
    };
}
namespace winrt::Editor::factory_implementation
{
    struct RenderingProperty : RenderingPropertyT<RenderingProperty, implementation::RenderingProperty>
    {
    };
}
