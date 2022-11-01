#include "pch.h"
#include "ActorComponent.h"
#include "ActorComponent.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    ActorComponent::ActorComponent(hstring const& title)
        :m_title(title)
    {       
    }
    hstring ActorComponent::Title()
    {
        return m_title;
    }
    void ActorComponent::Title(hstring const& value)
    {
        if (m_title != value)
        {
            m_title = value;
            m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Title" });
        }
    }
    winrt::event_token ActorComponent::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
       return m_propertyChanged.add(handler);                
    }
    void ActorComponent::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
