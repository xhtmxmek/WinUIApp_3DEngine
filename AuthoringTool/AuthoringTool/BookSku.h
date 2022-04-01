#pragma once
#include "BookSku.g.h"

namespace winrt::AuthoringTool::implementation
{
    struct BookSku : BookSkuT<BookSku>
    {
        BookSku() = delete;

        BookSku(hstring const& title);
        hstring Title();
        void Title(hstring const& value);
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token);
    private:
        winrt::hstring m_title;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct BookSku : BookSkuT<BookSku, implementation::BookSku>
    {
    };
}
