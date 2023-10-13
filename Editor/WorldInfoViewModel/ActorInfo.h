#pragma once
#include "ActorInfo.g.h"


namespace winrt::Editor::implementation
{
    struct ActorInfo : ActorInfoT<ActorInfo>
    {
        ActorInfo() = delete;

        ActorInfo(hstring const& name);
        hstring Name();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> ComponentInfos();
    private:
        hstring name_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> componentInfos_;
    };
}

namespace winrt::Editor::factory_implementation
{
    struct ActorInfo : ActorInfoT<ActorInfo, implementation::ActorInfo>
    {
    };
}
