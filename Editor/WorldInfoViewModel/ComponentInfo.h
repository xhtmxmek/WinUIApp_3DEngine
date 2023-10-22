#pragma once
#include "ObservableObject.h"
#include "nativeClasses/CategoryInfo.h"
#include "ComponentInfo.g.h"

namespace Engine
{
    namespace Component
    {
        class ComponentBase;
    }
}

namespace EditorNativeClasses
{
    class CategoryInfo;
}

namespace winrt::Editor::implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo, Editor::implementation::ObservableObject>
    {
        ComponentInfo() = delete;

        ComponentInfo(hstring const& name);

    public:
        void UpdateComponentDetail(hstring ownwerActorName, hstring componentName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
    private:
        void CreateCategoryProxy(Engine::Component::PropertyBase* nativeProperty, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
    public:
        hstring Name();
        void Name(hstring const& value);

    private:
        hstring name_;

        std::weak_ptr<Engine::Component::ComponentBase> nativeComponent_;
        std::map<std::wstring, std::shared_ptr<EditorNativeClasses::CategoryInfo>> categories_;

    };
}

namespace winrt::Editor::factory_implementation
{
    struct ComponentInfo : ComponentInfoT<ComponentInfo, implementation::ComponentInfo>
    {
    };
}
