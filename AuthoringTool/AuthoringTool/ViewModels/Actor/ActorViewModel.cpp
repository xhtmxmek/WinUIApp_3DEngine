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
        //액터가 선택될때 엔진이 가지고 있는 액터의 정보를 넘김.
    }
    void ActorViewModel::SetActor(EngineInterface_WRC::ActorProxy const& actor)
    {   
        //actor.Components()
    }
}
