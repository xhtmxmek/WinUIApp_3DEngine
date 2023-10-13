#pragma once
#include "WorldInfoViewModel.g.h"


namespace winrt::Editor::implementation
{
    struct WorldInfoViewModel : WorldInfoViewModelT<WorldInfoViewModel>
    {
        WorldInfoViewModel();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ActorInfo> ActorInfos();
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ActorInfo> actorInfos_;
    };
}

namespace winrt::Editor::factory_implementation
{
    struct WorldInfoViewModel : WorldInfoViewModelT<WorldInfoViewModel, implementation::WorldInfoViewModel>
    {
    };
}
