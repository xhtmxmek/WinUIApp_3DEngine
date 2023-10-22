#include "pch.h"
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "CategoryInfo.h"
#include "Component/ComponentBase/ComponentBase.h"

namespace EditorNativeClasses
{
	std::shared_ptr<CategoryInfo> CreateCategory(winrt::hstring const& categoryName, winrt::Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
	{
		auto categoryInfo = std::make_shared<CategoryInfo>(categoryName);
		categoryInfo->Init(detailPanel);

		return categoryInfo;
	}

	CategoryInfo::CategoryInfo(winrt::hstring const& categoryName)
		:name_(categoryName)
	{
	}

	void CategoryInfo::Init(winrt::Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
	{
		layOut_.Content(panel_);
		layOut_.Header(winrt::box_value(name_));
		layOut_.IsExpanded(true);
		detailPanel.Children().Append(layOut_);
	}

	void CategoryInfo::InsertNewPropertyInfo(std::shared_ptr<PropertyInfo> const& inProp)
	{
		properties_.push_back(inProp);
		panel_.Children().Append(inProp->Panel());
	}

	std::shared_ptr<PropertyInfo> CreatePropertyInfoByNative(Engine::Component::PropertyBase* nativeProp)
	{
		if (nativeProp == nullptr)
			return nullptr;

		auto newProp = std::make_shared<PropertyInfo>(nativeProp, nativeProp->Name().c_str());
		newProp->Init();

		return newProp;
	}

	PropertyInfo::PropertyInfo(Engine::Component::PropertyBase* src, const winrt::hstring& name)
		: nativeProperty_(src),
		name_(name)
	{
	}

	void PropertyInfo::Init()
	{
		panel_.Orientation(Controls::Orientation::Horizontal);
		//layOut_.SetBinding(Microsoft::UI::Xaml::Controls::Expander::Visibility()
//	winrt::Windows::UI::Xaml::Data::Binding{ L"IsExpanderVisible", winrt::Windows::UI::Xaml::Data::BindingMode::TwoWay })
		if (nativeProperty_ == nullptr)
			return;

		Microsoft::UI::Xaml::Controls::TextBlock textBlock;
		textBlock.Text(nativeProperty_->Name());
		panel_.Children().Append(textBlock);

		switch (nativeProperty_->Type())
		{
		case Engine::Component::PropertyType::TypeBool:
		{
			Engine::Component::PropertyBool* boolProp = static_cast<Engine::Component::PropertyBool*>(nativeProperty_);

			Microsoft::UI::Xaml::Controls::CheckBox checkBox;
			checkBox.IsChecked(boolProp->Value());
			panel_.Children().Append(checkBox);
		}
		break;
		case Engine::Component::PropertyType::TypeVector3:
		{
			Engine::Component::PropertyVector3* vectorProp = static_cast<Engine::Component::PropertyVector3*>(nativeProperty_);

			Microsoft::UI::Xaml::Controls::TextBox xText;
			xText.Text(winrt::to_hstring(vectorProp->Value().x));
			Microsoft::UI::Xaml::Controls::TextBox yText;
			yText.Text(winrt::to_hstring(vectorProp->Value().y));
			Microsoft::UI::Xaml::Controls::TextBox zText;
			zText.Text(winrt::to_hstring(vectorProp->Value().z));

			panel_.Children().Append(xText);
			panel_.Children().Append(yText);
			panel_.Children().Append(zText);
		}
		break;
		case Engine::Component::PropertyType::TypePath:
		{
			//nativeProperty의 stingArray에 담긴 요소들을 담아야함. enumType 참조하여 수정하기
			Controls::ListBox box;
			//box.
			box.Items().Append(winrt::box_value(L"test1"));
			box.Items().Append(winrt::box_value(L"test2"));
			box.Items().Append(winrt::box_value(L"test3"));
			box.Items().Append(winrt::box_value(L"test4"));
			box.Items().Append(winrt::box_value(L"test5"));
			panel_.Children().Append(box);
		}
		break;
		}
	}
	const winrt::Microsoft::UI::Xaml::Controls::StackPanel& PropertyInfo::Panel()
	{
		return panel_;
	}
}
