#pragma once
#include "ObservableObject.g.h"

namespace winrt::Editor::implementation
{
    struct ObservableObject : ObservableObjectT<ObservableObject>
    {
        ObservableObject() = default;

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

    protected:
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;
    };
}
