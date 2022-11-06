#pragma once
#include "ActorComponentProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorComponentProxy : ActorComponentProxyT<ActorComponentProxy>
    {
        ActorComponentProxy() = default;

        winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> Properties();
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorComponentProxy : ActorComponentProxyT<ActorComponentProxy, implementation::ActorComponentProxy>
    {
    };
}
