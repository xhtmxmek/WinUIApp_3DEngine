#include "pch.h"
#include "BookstoreViewModel.h"
#include "BookstoreViewModel.g.cpp"
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Syndication.h>

namespace winrt::AuthoringTool::implementation
{
    BookstoreViewModel::BookstoreViewModel()
    {
        m_bookSku = winrt::make<AuthoringTool::implementation::BookSku>(L"Atticus");
        GetUserAsync();
    }

    AuthoringTool::BookSku BookstoreViewModel::BookSku()
    {
        return m_bookSku;
    }
    winrt::Windows::Foundation::IAsyncAction BookstoreViewModel::GetUserAsync()
    {
        //winrt::Windows::Foundation::Uri rssFeedUri{ L"http://jsonplaceholder.typicode.com/users/1" };
        //winrt::Windows::Web::Syndication::SyndicationClient syndicationClient;
        //winrt::Windows::Web::Syndication::SyndicationFeed syndicationFeed{ co_await syndicationClient.RetrieveFeedAsync(rssFeedUri) };

        winrt::Windows::Web::Http::HttpClient httpClient;
        winrt::Windows::Foundation::Uri jsonAdress{ L"http://jsonplaceholder.typicode.com/users/1" };
        auto httpResopnse = co_await httpClient.GetStringAsync( jsonAdress );
        Windows::Data::Json::JsonObject jsonObj;
        if (Windows::Data::Json::JsonObject::TryParse(httpResopnse, jsonObj))
        {
            winrt::Windows::Data::Json::JsonValueType type = jsonObj.ValueType();
            int k = 5;
        }

    }
}