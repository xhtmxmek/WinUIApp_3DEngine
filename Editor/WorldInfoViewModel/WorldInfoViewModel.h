#pragma once
#include "WorldInfoViewModel.g.h"


namespace winrt::Editor::implementation
{
    struct WorldInfoViewModel : WorldInfoViewModelT<WorldInfoViewModel>
    {
        WorldInfoViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ActorLabel> ActorLabels();
        void UpdateWorldInfoProxy();

        winrt::Editor::ActorDetail SelectedActorDetail();
        void UpdateSelectedActorDetail(hstring actorName);
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ActorLabel> actorlabels_;
        winrt::Editor::ActorDetail selectedActorDetail_ = { nullptr };
    };
}

namespace winrt::Editor::factory_implementation
{
    struct WorldInfoViewModel : WorldInfoViewModelT<WorldInfoViewModel, implementation::WorldInfoViewModel>
    {
    };
}
