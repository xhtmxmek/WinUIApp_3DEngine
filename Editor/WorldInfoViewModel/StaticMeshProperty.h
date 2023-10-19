#pragma once
#include "PropertyBase.h"
#include "StaticMeshProperty.g.h"


namespace winrt::Editor::implementation
{
    struct StaticMeshProperty : StaticMeshPropertyT<StaticMeshProperty, Editor::implementation::PropertyBase>
    {
        StaticMeshProperty() = delete;

        StaticMeshProperty(hstring const& name);

        hstring Name();

        hstring MeshAsset();
        void MeshAsset(hstring const& value);

        winrt::Microsoft::UI::Xaml::Visibility PropertyVisible();
        void PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value);
    private:
        hstring name_;
        winrt::Microsoft::UI::Xaml::Visibility propertyVisible_;
        hstring meshAsset_;
    };
}
namespace winrt::Editor::factory_implementation
{
    struct StaticMeshProperty : StaticMeshPropertyT<StaticMeshProperty, implementation::StaticMeshProperty>
    {
    };
}
