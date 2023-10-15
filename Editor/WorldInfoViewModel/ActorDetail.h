#pragma once
#include "ActorDetail.g.h"

namespace winrt::Editor::implementation
{
    struct ActorDetail : ActorDetailT<ActorDetail>
    {
        ActorDetail() = delete;

        ActorDetail(hstring const& name);

        hstring Name();
        void Name(hstring const& value);

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> ComponentInfos();

        winrt::Microsoft::UI::Xaml::Visibility Visible();
        void Visible(winrt::Microsoft::UI::Xaml::Visibility const& value);

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        winrt::Microsoft::UI::Xaml::Visibility visible_;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> componentInfos_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler>propertyChanged_;

    };
}
namespace winrt::Editor::factory_implementation
{
    struct ActorDetail : ActorDetailT<ActorDetail, implementation::ActorDetail>
    {
    };
}
