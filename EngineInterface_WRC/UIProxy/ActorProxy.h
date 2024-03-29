#pragma once
#include "ActorProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorProxy : ActorProxyT<ActorProxy>
    {
        ActorProxy() = default;

        ActorProxy(hstring const& name, hstring const& type);
        hstring Name();
        void Name(hstring const& value);
        hstring Type();
        void Type(hstring const& value);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorProxy> ChildActors();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponentProxy> Components();
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token);
    private:
        hstring name_;
        hstring type_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorProxy> childActors_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponentProxy> components_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorProxy : ActorProxyT<ActorProxy, implementation::ActorProxy>
    {
    };
}
