#pragma once
#include "ActorComponent.g.h"
#include "ActorProperty.h"

namespace winrt::AuthoringTool::implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent>
    {
        ActorComponent() = delete;

        ActorComponent(hstring const& name);
        hstring Name();

        bool Visible();
        void Visible(bool value);

        winrt::Windows::Foundation::Numerics::float3 Position();
        void Position(winrt::Windows::Foundation::Numerics::float3 const& value);
        winrt::Windows::Foundation::Numerics::float3 Rotation();
        void Rotation(winrt::Windows::Foundation::Numerics::float3 const& value);
        winrt::Windows::Foundation::Numerics::float3 Scale();
        void Scale(winrt::Windows::Foundation::Numerics::float3 const& value);

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorProperty> Properties();
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:        
        Windows::Foundation::Collections::IObservableVector<AuthoringTool::ActorProperty> _properties;
        winrt::hstring _name;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChanged;

        bool _visible;
        winrt::Windows::Foundation::Numerics::float3 position_;
        winrt::Windows::Foundation::Numerics::float3 rotation_;
        winrt::Windows::Foundation::Numerics::float3 scale_;



    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent, implementation::ActorComponent>
    {
    };
}
