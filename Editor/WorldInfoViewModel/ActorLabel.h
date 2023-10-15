#pragma once
#include "ActorLabel.g.h"


namespace winrt::Editor::implementation
{
    struct ActorLabel : ActorLabelT<ActorLabel>
    {
        ActorLabel() = delete;

        ActorLabel(hstring const& name);
        hstring Name();
    private:
        hstring name_;
        //hstring type - enum을 찾아야함
    };
}

namespace winrt::Editor::factory_implementation
{
    struct ActorLabel : ActorLabelT<ActorLabel, implementation::ActorLabel>
    {
    };
}
