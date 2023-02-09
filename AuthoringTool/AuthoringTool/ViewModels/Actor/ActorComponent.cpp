#include "pch.h"
#include "ActorComponent.h"
#include "ActorComponent.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorComponent::ActorComponent(hstring const& name)
        :_name(name)
    {
        _properties = winrt::single_threaded_observable_vector<AuthoringTool::ActorProperty>();
    }
    hstring ActorComponent::Name()
    {
        return _name;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorProperty> ActorComponent::Properties()
    {
        return _properties;
    }
    winrt::event_token ActorComponent::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return _propertyChanged.add(handler);
    }
    void ActorComponent::PropertyChanged(winrt::event_token const& token) noexcept
    {
        return _propertyChanged.remove(token);
    }
}
