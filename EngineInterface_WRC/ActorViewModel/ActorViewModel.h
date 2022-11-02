#pragma once
#include "ActorComponent.h"
#include "ActorViewModel.g.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct ActorViewModel : ActorViewModelT<ActorViewModel>
    {
        ActorViewModel();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorComponent> Components();
    private:        
        Windows::Foundation::Collections::IObservableVector<EngineInterface_WRC::ActorComponent> ComponentsData;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct ActorViewModel : ActorViewModelT<ActorViewModel, implementation::ActorViewModel>
    {
    };
}
