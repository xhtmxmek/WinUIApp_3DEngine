#include "pch.h"
#include "ActorViewModel.h"
#include "ActorViewModel.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorViewModel::ActorViewModel()
        :selectedComponent_(L"")
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
    winrt::AuthoringTool::ActorComponent ActorViewModel::SelectedComponent()
    {
        return selectedComponent_;
    }
    void ActorViewModel::SelectedComponent(winrt::AuthoringTool::ActorComponent const& value)
    {
        selectedComponent_ = value;
    }

    void ActorViewModel::SetActor(EngineInterface_WRC::ActorProxy const& actor)
    {   
        //actor.Components()
    }
}
