#include "pch.h"
#include "TransformProperty.h"
#include "TransformProperty.g.cpp"


namespace winrt::Editor::implementation
{
    TransformProperty::TransformProperty(hstring const& name)
        :name_(name), position_(0.f)
    {
     
    }

    hstring TransformProperty::Name()
    {
        return name_;
    }

    winrt::Windows::Foundation::Numerics::float3 TransformProperty::Position()
    {
        return position_;
    }

    void TransformProperty::Position(winrt::Windows::Foundation::Numerics::float3 const& value)
    {
        if (position_ != value)
        {
            position_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Position" });
        }
    }

    winrt::event_token TransformProperty::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }

    void TransformProperty::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}
