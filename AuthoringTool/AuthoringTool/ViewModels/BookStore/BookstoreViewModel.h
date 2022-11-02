// BookstoreViewModel.h
#pragma once
#include "BookstoreViewModel.g.h"
#include "BookSku.h"

namespace winrt::AuthoringTool::implementation
{
    struct BookstoreViewModel : BookstoreViewModelT<BookstoreViewModel>
    {
        BookstoreViewModel();

        AuthoringTool::BookSku BookSku();

    private:
        AuthoringTool::BookSku m_bookSku{ nullptr };
        winrt::Windows::Foundation::IAsyncAction GetUserAsync();
    };
}
namespace winrt::AuthoringTool::factory_implementation
{
    struct BookstoreViewModel : BookstoreViewModelT<BookstoreViewModel, implementation::BookstoreViewModel>
    {
    };
}
