#include "pch.h"
#include "ActorLabel.h"
#include "ActorLabel.g.cpp"


namespace winrt::Editor::implementation
{
    ActorLabel::ActorLabel(hstring const& name)
        :name_(name)
    {
    }

    hstring ActorLabel::Name()
    {
        return name_;
    }
}
