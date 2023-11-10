#include "pch.h"
#include "ComponentInfo.h"
//#include "TransformProperty.h"
#include "EngineCore.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "ComponentInfo.g.cpp"

namespace winrt::Editor::implementation
{
	ComponentInfo::ComponentInfo(hstring const& name)
		:name_(name)
		//transform_(L"Transform"), 
		//staticMesh_(L"StaticMesh"),
		//rendering_(L"Rendering")
	{
	}

	void ComponentInfo::UpdateComponentDetail(hstring ownwerActorName, hstring componentName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
	{
		auto engine = Engine::GetRenderingEngine();
		auto nativeActor = weak_ptr<Engine::Level::Actor>(engine->GetActor(winrt::to_string(ownwerActorName)));
		if (nativeActor.lock() == nullptr)
			return;

		if (nativeActor.expired())
			return;

		nativeComponent_ = nativeActor.lock()->GetComponentByName(winrt::to_string(componentName));
		if (nativeComponent_.lock() == nullptr)
			return;

		if (nativeComponent_.expired())
			return;

		auto pos = nativeComponent_.lock()->GetComponentTransform().GetPositionPtrToEditor();
		auto rot = nativeComponent_.lock()->GetComponentTransform().GetRotationPtrToEditor();
		auto scale = nativeComponent_.lock()->GetComponentTransform().GetScalePtrToEditor();

		CreateCategoryProxy(pos, detailPanel);
		CreateCategoryProxy(rot, detailPanel);
		CreateCategoryProxy(scale, detailPanel);

		//native의 Type을 판별하여 해당하는 타입의 Property 생성하여 properties에 넣기
		//각 Property는 값이 변경되면 연결된 nativeProperty의 OnChangedEvent를 호출한다.
		for (auto i = 0; i < nativeComponent_.lock()->NumProperty(); i++)
		{
			CreateCategoryProxy(nativeComponent_.lock()->GetProperty(i), detailPanel);
		}
	}

	void ComponentInfo::CreateCategoryProxy(Engine::Component::PropertyBase* nativeProperty, 
		Controls::StackPanel const& detailPanel)
	{
		auto newProp = EditorNativeClasses::CreatePropertyInfoByNative(nativeProperty);
		if (newProp == nullptr)
			return;

		const auto category = nativeProperty->Category();
		auto iter = categories_.find(category);
		if (iter != categories_.end())
		{
			auto categoryInfo = iter->second;
			if (categoryInfo == nullptr)
				return;

			categoryInfo->InsertNewPropertyInfo(newProp);
		}
		else
		{
			auto newCategoryInfo = EditorNativeClasses::CreateCategory(category.c_str(), detailPanel);
			if (newCategoryInfo != nullptr)
			{
				newCategoryInfo->InsertNewPropertyInfo(newProp);
				categories_.insert({ category, newCategoryInfo });
			}
		}
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
}
