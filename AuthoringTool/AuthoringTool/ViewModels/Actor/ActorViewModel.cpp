#include "pch.h"
#include "ActorViewModel.h"
#include "ActorViewModel.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorViewModel::ActorViewModel()
    {
        _components = winrt::single_threaded_observable_vector<AuthoringTool::ActorComponent>();        
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorComponent> ActorViewModel::Components()
    {
        return _components;
    }

    hstring ActorViewModel::Name()
    {
        //return _name;
        return L"ActorName";
    }
    void ActorViewModel::Name(hstring const& value)
    {
        _name = value;
        //���Ͱ� ���õɶ� ������ ������ �ִ� ������ ������ �ѱ�.
    }
    void ActorViewModel::SetActor(EngineInterface_WRC::ActorProxy const& actor)
    {   
        //actor.Components()
    }
}
