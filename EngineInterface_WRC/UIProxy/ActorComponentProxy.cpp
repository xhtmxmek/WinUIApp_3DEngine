#include "pch.h"
#include "ActorComponentProxy.h"
#include "ActorComponentProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorComponentProxy::ActorComponentProxy(const hstring& name)
        :name_(name)
    {
        properties_ = Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ComponentPropertyProxy>();
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> ActorComponentProxy::Properties()
    {
        return properties_;
    }

    hstring ActorComponentProxy::Name()
    {
        return name_;
    }
}
