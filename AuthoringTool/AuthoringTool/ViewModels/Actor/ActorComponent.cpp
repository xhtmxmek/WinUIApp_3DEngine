#include "pch.h"
#include "ActorComponent.h"
#include "ActorComponent.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorComponent::ActorComponent(hstring const& name)
        :_name(name),
        _visible(true),
        position_(0.0f, 0.0f, 0.0f),
        rotation_(0.0f, 0.0f, 0.0f),
        scale_(1.0f, 1.0f, 1.0f)
    {
        _properties = winrt::single_threaded_observable_vector<AuthoringTool::ActorProperty>();
    }
    hstring ActorComponent::Name()
    {
        return _name;
    }
    bool ActorComponent::Visible()
    {
        return _visible;
    }
    void ActorComponent::Visible(bool value)
    {
        _visible = value;
    }

    winrt::Windows::Foundation::Numerics::float3 ActorComponent::Position()
    {
        return position_;
    }
    void ActorComponent::Position(winrt::Windows::Foundation::Numerics::float3 const& value)
    {
        position_ = value;
    }
    winrt::Windows::Foundation::Numerics::float3 ActorComponent::Rotation()
    {
        return rotation_;
    }
    void ActorComponent::Rotation(winrt::Windows::Foundation::Numerics::float3 const& value)
    {
        rotation_ = value;
    }
    winrt::Windows::Foundation::Numerics::float3 ActorComponent::Scale()
    {
        return scale_;
    }
    void ActorComponent::Scale(winrt::Windows::Foundation::Numerics::float3 const& value)
    {
        scale_ = value;
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
