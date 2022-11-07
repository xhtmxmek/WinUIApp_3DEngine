#pragma once
#include "ActorProxy.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorProxy : ActorProxyT<ActorProxy>
    {
        ActorProxy();
        hstring Name();
        void Name(hstring const& value);
        winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ActorComponentProxy> Components();
    private:
        hstring name_;
        Windows::Foundation::Collections::IVector< EngineInterface_WRC::ActorComponentProxy> components_;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorProxy : ActorProxyT<ActorProxy, implementation::ActorProxy>
    {
    };
}
