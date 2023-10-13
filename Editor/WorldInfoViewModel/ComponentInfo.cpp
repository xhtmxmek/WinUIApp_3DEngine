#include "pch.h"
#include "ComponentInfo.h"
#include "ComponentInfo.g.cpp"


namespace winrt::Editor::implementation
{
    ComponentInfo::ComponentInfo(hstring const& name)
        :name_(name),
        transform_(L"Transform"), 
        staticMesh_(L"StaticMesh"),
        rendering_(L"Rendering")
    {
    }

    hstring ComponentInfo::Name()
    {
        return name_;
    }

    bool ComponentInfo::HasStaticMeshProperty()
    {
        return (staticMesh_ != nullptr);
    }

    winrt::Editor::StaticMeshProperty ComponentInfo::StaticMesh()
    {
        return staticMesh_;
    }


    bool ComponentInfo::HasTransform()
    {
        return (transform_ != nullptr);
    }

    void ComponentInfo::Transform(winrt::Editor::TransformProperty const& value)
    {
        transform_ = value;
    }

    winrt::Editor::TransformProperty ComponentInfo::Transform()
    {
        return transform_;
    }

    bool ComponentInfo::HasRenderingProperty()
    {
        return rendering_ != nullptr;
    }

    winrt::Editor::RenderingProperty ComponentInfo::Rendering()
    {
        return rendering_;
    }
}
