#include "pch.h"
#include "ActorLabel.h"
#include "ActorLabel.g.cpp"


namespace winrt::Editor::implementation
{
    ActorLabel::ActorLabel(hstring const& name, hstring const& classtype)
        :name_(name),
        classType_(classtype)
    {
    }

    hstring ActorLabel::Name()
    {
        return name_;
    }
    hstring ActorLabel::ClassName()
    {
        return classType_;
    }
}
