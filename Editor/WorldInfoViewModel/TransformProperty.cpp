#include "pch.h"
#include "TransformProperty.h"
#include "TransformProperty.g.cpp"


namespace winrt::Editor::implementation
{
    TransformProperty::TransformProperty(hstring const& name)
        :name_(name), 
        position_(0.f, 0.f, 0.f),
        propertyVisible_(Microsoft::UI::Xaml::Visibility::Visible)
    {
     
    }

    hstring TransformProperty::Name()
    {
        return name_;
    }

    Editor::Vector3Single TransformProperty::Position()
    {
        return position_;
    }

    void TransformProperty::Position(Editor::Vector3Single const& value)
    {
        if (position_ != value)
        {
            position_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Position" });
        }
    }

    winrt::Microsoft::UI::Xaml::Visibility TransformProperty::PropertyVisible()
    {
        return propertyVisible_;
    }

    void TransformProperty::PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value)
    {
        if (propertyVisible_ != value)
        {
            propertyVisible_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"PropertyVisible" });
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
