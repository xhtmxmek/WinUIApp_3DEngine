#include "pch.h"
#include "ActorProxy.h"
#include "ActorProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorProxy::ActorProxy(hstring const& name, hstring const& type)
        :name_(name), type_(type)
    {     
        childActors_ = winrt::single_threaded_observable_vector<EngineInterface_WRC::ActorProxy>();
        components_ = winrt::single_threaded_observable_vector<EngineInterface_WRC::ActorComponentProxy>();
    }

    hstring ActorProxy::Name()
    {
        return name_;
    }

    void ActorProxy::Name(hstring const& value)
    {
        name_ = value;
    }

    hstring ActorProxy::Type()
    {
        return type_;
    }

    void ActorProxy::Type(hstring const& value)
    {
        type_ = value;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorProxy> ActorProxy::ChildActors()
    {
        return childActors_;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponentProxy> ActorProxy::Components()
    {
        return components_;
    }
}
