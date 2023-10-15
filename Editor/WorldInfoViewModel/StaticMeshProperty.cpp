#include "pch.h"
#include "StaticMeshProperty.h"
#include "StaticMeshProperty.g.cpp"


namespace winrt::Editor::implementation
{
    StaticMeshProperty::StaticMeshProperty(hstring const& name)
        :name_(name),
        meshAsset_(L""),
        propertyVisible_(Visibility::Collapsed)
    {
    }

    hstring StaticMeshProperty::Name()
    {
        return name_;
    }

    hstring StaticMeshProperty::MeshAsset()
    {
        return meshAsset_;
    }

    void StaticMeshProperty::MeshAsset(hstring const& value)
    {
        if (meshAsset_ != value)
        {
            meshAsset_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"MeshAsset" });
        }
    }

    winrt::Microsoft::UI::Xaml::Visibility StaticMeshProperty::PropertyVisible()
    {
        return propertyVisible_;
    }

    void StaticMeshProperty::PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value)
    {
        if (propertyVisible_ != value)
        {
            propertyVisible_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"PropertyVisible" });
        }
      
    }

    winrt::event_token StaticMeshProperty::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }

    void StaticMeshProperty::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}
