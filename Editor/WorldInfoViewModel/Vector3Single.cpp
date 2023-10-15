#include "pch.h"
#include "Vector3Single.h"
#include "Vector3Single.g.cpp"

namespace winrt::Editor::implementation
{
    Vector3Single::Vector3Single(float x, float y, float z)
    {
        value_.x = x;
        value_.y = y;
        value_.z = z;
    }

    float Vector3Single::X()
    {
        return value_.x;
    }
    void Vector3Single::X(float value)
    {
        if (value_.x != value)
        {
            value_.x = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"X" });
        }
    }
    float Vector3Single::Y()
    {
        return value_.y;
    }
    void Vector3Single::Y(float value)
    {
        if (value_.y != value)
        {
            value_.y= value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Y" });
        }
    }
    float Vector3Single::Z()
    {
        return value_.z;
    }
    void Vector3Single::Z(float value)
    {
        if (value_.z != value)
        {
            value_.z = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Z" });
        }
    }
    winrt::event_token Vector3Single::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }
    void Vector3Single::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}
