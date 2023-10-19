#pragma once
#include "PropertyBase.h"
#include "TransformProperty.g.h"


namespace winrt::Editor::implementation
{
    struct TransformProperty : TransformPropertyT<TransformProperty, Editor::implementation::PropertyBase>
    {
        TransformProperty() = delete;

        TransformProperty(hstring const& name);

        hstring Name();

        Editor::Vector3Single Position();
        void Position(Editor::Vector3Single const& value);

        winrt::Microsoft::UI::Xaml::Visibility PropertyVisible();
        void PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value);
    private:
        hstring name_;
        winrt::Microsoft::UI::Xaml::Visibility propertyVisible_;
        Editor::Vector3Single position_;

        winrt::event_token positionChangedToken;
        winrt::event_token rotationChangedToken;
        winrt::event_token scaleChangedToken;

    };
}
namespace winrt::Editor::factory_implementation
{
    struct TransformProperty : TransformPropertyT<TransformProperty, implementation::TransformProperty>
    {
    };
}
