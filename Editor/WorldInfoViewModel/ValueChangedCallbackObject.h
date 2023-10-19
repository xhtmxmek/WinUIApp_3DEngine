#pragma once
#include "ObservableObject.h"
#include "ValueChangedCallbackObject.g.h"

namespace winrt::Editor::implementation
{
    struct ValueChangedCallbackObject : ValueChangedCallbackObjectT<ValueChangedCallbackObject, Editor::implementation::ObservableObject>
    {
        ValueChangedCallbackObject() = default;

        winrt::event_token ValueChanged(winrt::Editor::ValueChangedCallback const& handler);
        void ValueChanged(winrt::event_token const& token) noexcept;
    private:
        winrt::event<winrt::Editor::ValueChangedCallback> valueChanged_;
    };
}
