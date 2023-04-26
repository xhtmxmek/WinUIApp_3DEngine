#include "pch.h"
#include "ActorComponentProxy.h"
#include "ActorComponentProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorComponentProxy::ActorComponentProxy(hstring const& name)
        :name_(name)
    {
        childComponents_ = winrt::single_threaded_observable_vector<EngineInterface_WRC::ActorComponentProxy>();
        properties_ = winrt::single_threaded_observable_vector<EngineInterface_WRC::ComponentPropertyProxy>();
    }
    hstring ActorComponentProxy::Name()
    {
        return name_;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponentProxy> ActorComponentProxy::ChildComponents()
    {
        return childComponents_;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ComponentPropertyProxy> ActorComponentProxy::Properties()
    {
        return properties_;
    }
}
