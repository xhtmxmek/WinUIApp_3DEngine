#pragma once
#include "TransformProperty.g.h"


namespace winrt::Editor::implementation
{
    struct TransformProperty : TransformPropertyT<TransformProperty>
    {
        TransformProperty() = delete;

        TransformProperty(hstring const& name);

        hstring Name();

        Editor::Vector3Single Position();
        void Position(Editor::Vector3Single const& value);

        winrt::Microsoft::UI::Xaml::Visibility PropertyVisible();
        void PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value);

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        winrt::Microsoft::UI::Xaml::Visibility propertyVisible_;
        Editor::Vector3Single position_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;

    };
}
namespace winrt::Editor::factory_implementation
{
    struct TransformProperty : TransformPropertyT<TransformProperty, implementation::TransformProperty>
    {
    };
}
