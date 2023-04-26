#pragma once
#include "ActorComponentProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorComponentProxy : ActorComponentProxyT<ActorComponentProxy>
    {
        ActorComponentProxy() = default;

        ActorComponentProxy(hstring const& name);
        hstring Name();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponentProxy> ChildComponents();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> Properties();
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponentProxy> childComponents_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> properties_;
        hstring name_;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorComponentProxy : ActorComponentProxyT<ActorComponentProxy, implementation::ActorComponentProxy>
    {
    };
}
