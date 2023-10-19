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

    void Vector3Single::SetValue(float x, float y, float z)
    {
        X(x);
        Y(y);
        Z(z);
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

            //valueChanged_();
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
            //valueChanged_();
        }
    }
}
