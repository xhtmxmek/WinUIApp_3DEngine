#pragma once
#include "ActorLabel.g.h"


namespace winrt::Editor::implementation
{
    struct ActorLabel : ActorLabelT<ActorLabel>
    {
        ActorLabel() = delete;

        ActorLabel(hstring const& name, hstring const& classtype);
        hstring Name();
        hstring ClassName();
    private:
        hstring name_;
        hstring classType_;
    };
}

namespace winrt::Editor::factory_implementation
{
    struct ActorLabel : ActorLabelT<ActorLabel, implementation::ActorLabel>
    {
    };
}
