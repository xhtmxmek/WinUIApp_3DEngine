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

    void ComponentInfo::Name(hstring const& value)
    {
        if (name_ != value)
        {
            name_ = value;
            propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    winrt::Editor::StaticMeshProperty ComponentInfo::StaticMesh()
    {
        return staticMesh_;
    }

    void ComponentInfo::Transform(winrt::Editor::TransformProperty const& value)
    {
        transform_ = value;
    }

    winrt::Editor::TransformProperty ComponentInfo::Transform()
    {
        return transform_;
    }

    winrt::Editor::RenderingProperty ComponentInfo::Rendering()
    {
        return rendering_;
    }
    winrt::event_token ComponentInfo::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return propertyChanged_.add(handler);
    }
    void ComponentInfo::PropertyChanged(winrt::event_token const& token) noexcept
    {
        propertyChanged_.remove(token);
    }
}
