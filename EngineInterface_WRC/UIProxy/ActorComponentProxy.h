#pragma once
#include "ActorComponentProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorComponentProxy : ActorComponentProxyT<ActorComponentProxy>
    {
        ActorComponentProxy();
        hstring Name();
        winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> Properties();
    private:
        hstring name_;
        Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> properties_;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorComponentProxy : ActorComponentProxyT<ActorComponentProxy, implementation::ActorComponentProxy>
    {
    };
}
