#include "pch.h"
#include "ActorViewModel.h"
#include "ActorViewModel.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::ActorComponent> ActorViewModel::Components()
    {
        throw hresult_not_implemented();
    }

    hstring ActorViewModel::Name()
    {
        return _name;
    }
    void ActorViewModel::Name(hstring const& value)
    {
        _name = value;
    }
}
