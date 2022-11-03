#include "pch.h"
#include "ActorComponent.h"
#include "ActorComponent.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorComponent::ActorComponent(hstring const& name)
        :_name(name)
    {        
    }
    hstring ActorComponent::Name()
    {
        return _name;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorProperty> ActorComponent::Properties()
    {
        throw hresult_not_implemented();
    }
}
