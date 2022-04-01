#include "pch.h"
#include "BookstoreViewModel.h"
#include "BookstoreViewModel.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    BookstoreViewModel::BookstoreViewModel()
    {
        m_bookSku = winrt::make<AuthoringTool::implementation::BookSku>(L"Atticus");
    }

    AuthoringTool::BookSku BookstoreViewModel::BookSku()
    {
        return m_bookSku;
    }
}