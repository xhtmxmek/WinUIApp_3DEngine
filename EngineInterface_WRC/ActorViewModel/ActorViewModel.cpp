#include "pch.h"
#include "ActorViewModel.h"
#include "ActorViewModel.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorViewModel::ActorViewModel()
    {
        //m_bookSku = winrt::make<Bookstore::implementation::BookSku>(L"Atticus");
        EngineInterface_WRC::ActorComponent component = winrt::make<EngineInterface_WRC::implementation::ActorComponent>(L"Hello");
        ComponentsData = winrt::single_threaded_observable_vector<ActorComponent>();
        ComponentsData.Append(m_bookSku);
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponent> ActorViewModel::Components()
    {
        throw hresult_not_implemented();
    }
}
