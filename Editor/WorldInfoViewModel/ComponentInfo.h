#pragma once
#include "ObservableObject.h"
#include "ComponentInfo.g.h"

namespace Engine
{
    namespace Component
    {
        class ComponentBase;
    }
}

namespace winrt::Editor::implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo, Editor::implementation::ObservableObject>
    {
        ComponentInfo() = delete;

        ComponentInfo(hstring const& name);

    public:
        void UpdateComponentDetail(hstring ownwerActorName, hstring componentName);
    public:
        hstring Name();
        void Name(hstring const& value);

        Windows::Foundation::Collections::IObservableVector<winrt::Editor::PropertyBase> Properties();
        
        winrt::Editor::TransformProperty Transform();        
        winrt::Editor::StaticMeshProperty StaticMesh();
        winrt::Editor::RenderingProperty Rendering();

    private:
        hstring name_;
        Windows::Foundation::Collections::IObservableVector<winrt::Editor::PropertyBase> properties_;

        winrt::Editor::TransformProperty transform_;
        winrt::Editor::StaticMeshProperty staticMesh_ = { nullptr };
        winrt::Editor::RenderingProperty rendering_ = { nullptr };        

        std::weak_ptr<Engine::Component::ComponentBase> nativeComponent_;

    };
}

namespace winrt::Editor::factory_implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo, implementation::ComponentInfo>
    {
    };
}
