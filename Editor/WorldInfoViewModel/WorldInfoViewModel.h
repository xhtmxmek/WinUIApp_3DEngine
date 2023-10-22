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
        void UpdateSelectedActorDetail(hstring actorName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
        void ClearSelectedActor(Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
        void UpdateSelectedComponent(hstring componentName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
        hstring OutlinerComment();
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
