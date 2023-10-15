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
        //hstring type - enum�� ã�ƾ���
    };
}

namespace winrt::Editor::factory_implementation
{
    struct ActorLabel : ActorLabelT<ActorLabel, implementation::ActorLabel>
    {
    };
}
