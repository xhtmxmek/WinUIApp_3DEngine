#include "pch.h"
#include "ActorDetail.h"
#include "ComponentInfo.h"
#include "ActorDetail.g.cpp"

namespace winrt::Editor::implementation
{
    ActorDetail::ActorDetail(hstring const& name)
        :name_(name)
    {
        componentInfos_ = winrt::single_threaded_observable_vector<Editor::ComponentInfo>();

    }

    hstring ActorDetail::Name()
    {
        return name_;
    }

    void ActorDetail::Name(hstring const& value)
    {
        if (name_ != value)
        {
            name_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ComponentInfo> ActorDetail::ComponentInfos()
    {
        return componentInfos_;
    }

    winrt::Microsoft::UI::Xaml::Visibility ActorDetail::Visible()
    {
        return visible_;
    }

    void ActorDetail::Visible(winrt::Microsoft::UI::Xaml::Visibility const& value)
    {
        if (visible_ != value)
        {
            visible_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Visible" });
        }
    }

    winrt::event_token ActorDetail::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }
    void ActorDetail::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}