#pragma once
#include "StaticMeshProperty.g.h"


namespace winrt::Editor::implementation
{
    struct StaticMeshProperty : StaticMeshPropertyT<StaticMeshProperty>
    {
        StaticMeshProperty() = delete;

        StaticMeshProperty(hstring const& name);

        hstring Name();

        hstring MeshAsset();
        void MeshAsset(hstring const& value);

        winrt::Microsoft::UI::Xaml::Visibility PropertyVisible();
        void PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value);

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        winrt::Microsoft::UI::Xaml::Visibility propertyVisible_;
        hstring meshAsset_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;
    };
}
namespace winrt::Editor::factory_implementation
{
    struct StaticMeshProperty : StaticMeshPropertyT<StaticMeshProperty, implementation::StaticMeshProperty>
    {
    };
}
