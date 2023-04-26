#include "pch.h"
#include "ComponentPropertyProxy.h"
#include "ComponentPropertyProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ComponentPropertyProxy::ComponentPropertyProxy(hstring const& name)
        :name_(name)
    {
        Microsoft::UI::Xaml::Controls::TextBlock textBlock;
        textBlock.Text(L"Hi");
        mappedControl_ = textBlock;
    }
    hstring ComponentPropertyProxy::Name()
    {
        return name_;
    }
    winrt::Microsoft::UI::Xaml::UIElement ComponentPropertyProxy::MappedControl()
    {
        return mappedControl_;
    }
    void ComponentPropertyProxy::MappedControl(winrt::Microsoft::UI::Xaml::UIElement const& value)
    {
        //if(mappedControl_.value != value.value)¿œ∂ß..
        mappedControl_ = value;
        propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"MappedControl" });
    }
    winrt::event_token ComponentPropertyProxy::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }
    void ComponentPropertyProxy::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}
