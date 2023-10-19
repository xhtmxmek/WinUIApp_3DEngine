#include "pch.h"
#include "RenderingProperty.h"
#include "RenderingProperty.g.cpp"


namespace winrt::Editor::implementation
{
    RenderingProperty::RenderingProperty(hstring const& name)
        :name_(name),
        visible_(false),
        propertyVisible_(Visibility::Collapsed)
    {
    }

    hstring RenderingProperty::Name()
    {
        return name_;
    }

    bool RenderingProperty::Visible()
    {
        return visible_;
    }

    void RenderingProperty::Visible(bool value)
    {
        if (visible_ != value)
        {
            visible_ = value;
            //PropertyChanged([this] {
            //    *this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Visible" }; 
            //    });
        }
    }

    winrt::Microsoft::UI::Xaml::Visibility RenderingProperty::PropertyVisible()
    {
        return propertyVisible_;
    }

    void RenderingProperty::PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value)
    {
        if (propertyVisible_ != value)
        {
            propertyVisible_ = value;
            //PropertyChanged([this] {
            //    *this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"PropertyVisible" }; 
            //    });
        }
    }
}
