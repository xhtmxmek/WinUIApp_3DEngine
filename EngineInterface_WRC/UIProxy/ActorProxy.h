#pragma once
#include "ActorProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorProxy : ActorProxyT<ActorProxy>
    {
        ActorProxy() = default;
        hstring Name();
        void Name(hstring const& value);
        winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ActorComponentProxy> Components();
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorProxy : ActorProxyT<ActorProxy, implementation::ActorProxy>
    {
    };
}
