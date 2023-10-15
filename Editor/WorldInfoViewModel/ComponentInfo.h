#pragma once
#include "ComponentInfo.g.h"

namespace winrt::Editor::implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo>
    {
        ComponentInfo() = delete;

        ComponentInfo(hstring const& name);

        hstring Name();
        void Name(hstring const& value);
        
        winrt::Editor::TransformProperty Transform();
        void Transform(winrt::Editor::TransformProperty const& value);

        winrt::Editor::StaticMeshProperty StaticMesh();
        winrt::Editor::RenderingProperty Rendering();

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        hstring name_;
        winrt::Editor::TransformProperty transform_ = { nullptr };
        winrt::Editor::StaticMeshProperty staticMesh_ = { nullptr };
        winrt::Editor::RenderingProperty rendering_ = { nullptr };

        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;

    };
}

namespace winrt::Editor::factory_implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo, implementation::ComponentInfo>
    {
    };
}
