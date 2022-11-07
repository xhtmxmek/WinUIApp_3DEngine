#include "pch.h"
#include "ActorProxy.h"
#include "ActorProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    hstring ActorProxy::Name()
    {
        throw hresult_not_implemented();
    }
    void ActorProxy::Name(hstring const& value)
    {
        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ActorComponentProxy> ActorProxy::Components()
    {
        throw hresult_not_implemented();
    }
}
