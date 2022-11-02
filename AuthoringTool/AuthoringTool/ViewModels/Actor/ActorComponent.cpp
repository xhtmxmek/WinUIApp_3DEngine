#include "pch.h"
#include "ActorComponent.h"
#include "ActorComponent.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorComponent::ActorComponent(hstring const& title)
        :BookTitle(title)
    {       
    }
    hstring ActorComponent::Title()
    {
        return BookTitle;
    }
    void ActorComponent::Title(hstring const& value)
    {
        if (BookTitle != value)
        {
            BookTitle = value;
            PropertyChanedEvent(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Title" });
        }
    }
    winrt::event_token ActorComponent::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
       return PropertyChanedEvent.add(handler);
    }
    void ActorComponent::PropertyChanged(winrt::event_token const& token) noexcept
    {
        PropertyChanedEvent.remove(token);
    }
}
