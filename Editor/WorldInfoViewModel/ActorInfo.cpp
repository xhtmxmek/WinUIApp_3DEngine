#include "pch.h"
#include "ActorInfo.h"
#include "ActorInfo.g.cpp"


namespace winrt::Editor::implementation
{
    ActorInfo::ActorInfo(hstring const& name)
        :name_(name)
    {
        componentInfos_ = winrt::single_threaded_observable_vector<Editor::ComponentInfo>();
    }

    hstring ActorInfo::Name()
    {
        return name_;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> ActorInfo::ComponentInfos()
    {
        return componentInfos_;
    }
}
