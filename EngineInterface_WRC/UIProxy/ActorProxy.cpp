#include "pch.h"
#include "ActorProxy.h"
#include "ActorProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorProxy::ActorProxy()
    {
        components_ = winrt::single_threaded_vector<EngineInterface_WRC::ActorComponentProxy>();
    }
    hstring ActorProxy::Name()
    {
        return name_;
    }
    void ActorProxy::Name(hstring const& value)
    {
        name_ = value;
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ActorComponentProxy> ActorProxy::Components()
    {
        return components_;
    }
}
