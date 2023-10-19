#include "pch.h"
#include "ObservableObject.h"
#include "ObservableObject.g.cpp"

namespace winrt::Editor::implementation
{
    winrt::event_token ObservableObject::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }
    void ObservableObject::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}
