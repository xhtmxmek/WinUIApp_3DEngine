#pragma once
#include "PropertyBase.h"
#include "RenderingProperty.g.h"


namespace winrt::Editor::implementation
{
    struct RenderingProperty : RenderingPropertyT<RenderingProperty, Editor::implementation::PropertyBase>
    {
        RenderingProperty() = delete;

        RenderingProperty(hstring const& name);
        hstring Name();
        bool Visible();
        void Visible(bool value);

        winrt::Microsoft::UI::Xaml::Visibility PropertyVisible();
        void PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value);

    private:
        hstring name_;
        Microsoft::UI::Xaml::Visibility propertyVisible_;
        bool visible_;
    };
}
namespace winrt::Editor::factory_implementation
{
    struct RenderingProperty : RenderingPropertyT<RenderingProperty, implementation::RenderingProperty>
    {
    };
}
