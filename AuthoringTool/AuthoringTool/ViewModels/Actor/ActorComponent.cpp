#include "pch.h"
#include "ActorComponent.h"
#include "ActorComponent.g.cpp"

namespace winrt::AuthoringTool::implementation
{
    ActorComponent::ActorComponent(hstring const& name)
        :_name(name)
    {
        transformGroupProperties_ = winrt::single_threaded_observable_vector<AuthoringTool::TransformGroupProperty>();
        rederingProperties_ = winrt::single_threaded_observable_vector<AuthoringTool::RenderingProperty>();
        staticMeshProperties_ = winrt::single_threaded_observable_vector<AuthoringTool::StaticMeshProperty>();

        //������ staticMeshComponent�̸� staticMesh�� �߰��ؾ��ϰ� skeletalMesh�� �ش� �޽��� �߰��ؾߵ�.
        auto newStaticMeshProperty = winrt::make<AuthoringTool::implementation::StaticMeshProperty>();
        staticMeshProperties_.Append(newStaticMeshProperty);        
    }
    hstring ActorComponent::Name()
    {
        return _name;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::TransformGroupProperty> ActorComponent::TransformGroupProperties()
    {
        return transformGroupProperties_;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::RenderingProperty> ActorComponent::RenderingProperties()
    {
        return rederingProperties_;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::AuthoringTool::StaticMeshProperty> ActorComponent::StaticMeshProperties()
    {
        return staticMeshProperties_;
    }

    winrt::event_token ActorComponent::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return _propertyChanged.add(handler);
    }
    void ActorComponent::PropertyChanged(winrt::event_token const& token) noexcept
    {
        return _propertyChanged.remove(token);
    }
}
