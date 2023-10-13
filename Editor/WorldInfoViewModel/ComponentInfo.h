#pragma once
#include "ComponentInfo.g.h"

namespace winrt::Editor::implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo>
    {
        ComponentInfo() = delete;

        ComponentInfo(hstring const& name);

        hstring Name();
        
        bool HasTransform();
        winrt::Editor::TransformProperty Transform();
        void Transform(winrt::Editor::TransformProperty const& value);

        bool HasStaticMeshProperty();
        winrt::Editor::StaticMeshProperty StaticMesh();

        bool HasRenderingProperty();
        winrt::Editor::RenderingProperty Rendering();

    private:
        hstring name_;
        winrt::Editor::TransformProperty transform_ = { nullptr };
        winrt::Editor::StaticMeshProperty staticMesh_ = { nullptr };
        winrt::Editor::RenderingProperty rendering_ = { nullptr };
    };
}

namespace winrt::Editor::factory_implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo, implementation::ComponentInfo>
    {
    };
}
