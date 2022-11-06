#include "pch.h"
#include "ActorProperty.h"
#include "ActorProperty.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorProperty::ActorProperty(hstring const& name):_name(name)
    {        
    }
    hstring ActorProperty::Name()
    {
        return _name;
    }
    void ActorProperty::Name(hstring const& value)
    {
        if (_name != value)
        {
            _name = value;
            _propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }
    winrt::event_token ActorProperty::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return _propertyChanged.add(handler);
    }
    void ActorProperty::PropertyChanged(winrt::event_token const& token) noexcept
    {
        return _propertyChanged.remove(token);
    }
}
