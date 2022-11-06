#include "pch.h"
#include "ActorComponentProxy.h"
#include "ActorComponentProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    winrt::Windows::Foundation::Collections::IVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> ActorComponentProxy::Properties()
    {
        throw hresult_not_implemented();
    }
}
