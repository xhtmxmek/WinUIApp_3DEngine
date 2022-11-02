#include "pch.h"
#include "ActorViewModel.h"
#include "ActorViewModel.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorViewModel::ActorViewModel()
    {
        //m_bookSku = winrt::make<Bookstore::implementation::BookSku>(L"Atticus");
        EngineInterface_WRC::ActorComponent component = winrt::make<EngineInterface_WRC::implementation::ActorComponent>(L"Hello");
        ComponentsData = winrt::single_threaded_observable_vector<EngineInterface_WRC::ActorComponent>();
        ComponentsData.Append(component);
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponent> ActorViewModel::Components()
    {
        return ComponentsData;
    }
}
