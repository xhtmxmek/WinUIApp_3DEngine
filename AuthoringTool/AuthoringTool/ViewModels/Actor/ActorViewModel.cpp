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
        ////Test Code
        //for (int i = 0; i < 5; i++)
        //{
        //    hstring componentName = L"TestComponent_" + to_hstring(i);
        //    AuthoringTool::ActorComponent component = winrt::make<AuthoringTool::implementation::ActorComponent>(componentName);
        //    AuthoringTool::ActorProperty property = winrt::make<AuthoringTool::implementation::ActorProperty>(L"TestProperty_1");
        //    AuthoringTool::ActorProperty property2 = winrt::make<AuthoringTool::implementation::ActorProperty>(L"TestProperty_2");
        //    AuthoringTool::ActorProperty property3 = winrt::make<AuthoringTool::implementation::ActorProperty>(L"TestProperty_3");
        //    component.Properties().Append(property);
        //    component.Properties().Append(property2);
        //    component.Properties().Append(property3);
        //    _components.Append(component);
        //}

        actor.Components()
    }
}
