#include "pch.h"
#include "ActorProxy.h"
#include "ActorProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ActorComponentProxy> ActorProxy::Components()
    {
        throw hresult_not_implemented();
    }
}
