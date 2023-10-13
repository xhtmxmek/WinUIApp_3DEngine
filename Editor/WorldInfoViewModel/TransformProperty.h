#pragma once
#include "TransformProperty.g.h"


namespace winrt::Editor::implementation
{
    struct TransformProperty : TransformPropertyT<TransformProperty>
    {
        TransformProperty() = delete;

        TransformProperty(hstring const& name);
        hstring Name();
        winrt::Windows::Foundation::Numerics::float3 Position();
        void Position(winrt::Windows::Foundation::Numerics::float3 const& value);
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        winrt::Windows::Foundation::Numerics::float3 position_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;

    };
}
namespace winrt::Editor::factory_implementation
{
    struct TransformProperty : TransformPropertyT<TransformProperty, implementation::TransformProperty>
    {
    };
}
