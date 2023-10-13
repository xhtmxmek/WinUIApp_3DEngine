#include "pch.h"
#include "WorldInfoViewModel.h"
#include "WorldInfoViewModel.g.cpp"


namespace winrt::Editor::implementation
{
    WorldInfoViewModel::WorldInfoViewModel()
    {
        actorInfos_ = winrt::single_threaded_observable_vector<Editor::ActorInfo>();
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ActorInfo> WorldInfoViewModel::ActorInfos()
    {
        return actorInfos_;
    }
}
