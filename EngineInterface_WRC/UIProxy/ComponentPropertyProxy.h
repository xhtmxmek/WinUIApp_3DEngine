#pragma once
#include "ComponentPropertyProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ComponentPropertyProxy : ComponentPropertyProxyT<ComponentPropertyProxy>
    {
        ComponentPropertyProxy() = default;

        hstring Value();
        void Value(hstring const& value);
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ComponentPropertyProxy : ComponentPropertyProxyT<ComponentPropertyProxy, implementation::ComponentPropertyProxy>
    {
    };
}
