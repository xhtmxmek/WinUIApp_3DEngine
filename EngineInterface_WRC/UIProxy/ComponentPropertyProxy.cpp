#include "pch.h"
#include "ComponentPropertyProxy.h"
#include "ComponentPropertyProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    hstring ComponentPropertyProxy::Value()
    {
        throw hresult_not_implemented();
    }
    void ComponentPropertyProxy::Value(hstring const& value)
    {
        throw hresult_not_implemented();
    }
}
