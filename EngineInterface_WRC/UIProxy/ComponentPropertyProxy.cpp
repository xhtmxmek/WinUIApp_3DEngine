#include "pch.h"
#include "ComponentPropertyProxy.h"
#include "ComponentPropertyProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    hstring ComponentPropertyProxy::Name()
    {
        return name_;
    }
    hstring ComponentPropertyProxy::Value()
    {
        return value_;
    }
    void ComponentPropertyProxy::Value(hstring const& value)
    {
        value_ = value;
    }
}
