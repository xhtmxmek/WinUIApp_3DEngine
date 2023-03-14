#pragma once
#include "ActorComponent.g.h"
#include "ActorProperty.h"
#include "StaticMeshProperty.h"

namespace winrt::AuthoringTool::implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent>
    {
        ActorComponent() = delete;

        ActorComponent(hstring const& name);
        hstring Name();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::TransformGroupProperty> TransformGroupProperties();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::RenderingProperty> RenderingProperties();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::StaticMeshProperty> StaticMeshProperties();

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:        
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::TransformGroupProperty> transformGroupProperties_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::RenderingProperty> rederingProperties_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::StaticMeshProperty> staticMeshProperties_;        
        winrt::hstring _name;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChanged;

    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct ActorComponent : ActorComponentT<ActorComponent, implementation::ActorComponent>
    {
    };
}
