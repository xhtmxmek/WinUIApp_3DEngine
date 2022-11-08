#pragma once
#include "ComponentPropertyProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ComponentPropertyProxy : ComponentPropertyProxyT<ComponentPropertyProxy>
    {
        ComponentPropertyProxy() = default;

        hstring Name();
        hstring Value();
        void Value(hstring const& value);
    private:
        hstring name_;
        hstring value_;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ComponentPropertyProxy : ComponentPropertyProxyT<ComponentPropertyProxy, implementation::ComponentPropertyProxy>
    {
    };
}
