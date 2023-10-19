#include "pch.h"
#include "ValueChangedCallbackObject.h"
#include "ValueChangedCallbackObject.g.cpp"

namespace winrt::Editor::implementation
{
    winrt::event_token ValueChangedCallbackObject::ValueChanged(winrt::Editor::ValueChangedCallback const& handler)
    {
        return valueChanged_.add(handler);
    }
    void ValueChangedCallbackObject::ValueChanged(winrt::event_token const& token) noexcept
    {
        valueChanged_.remove(token);
    }
}
