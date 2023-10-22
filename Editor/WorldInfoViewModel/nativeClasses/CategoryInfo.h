#pragma once

namespace Engine
{
	namespace Component
	{
		class PropertyBase;
	}
}

namespace EditorNativeClasses
{
	class PropertyInfo
	{
	public:
		PropertyInfo(Engine::Component::PropertyBase* src, const winrt::hstring& name);
		void Init();
		const winrt::Microsoft::UI::Xaml::Controls::StackPanel& Panel();
	private:
		winrt::Microsoft::UI::Xaml::Controls::StackPanel panel_;
		winrt::hstring name_;
		Engine::Component::PropertyBase* nativeProperty_;
		//vector propetyInfo
	};

	class CategoryInfo
	{
	public:
		CategoryInfo(winrt::hstring const& categoryName);
		void Init(winrt::Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
		void InsertNewPropertyInfo(std::shared_ptr<PropertyInfo> const& inProp);
	private:
		winrt::Microsoft::UI::Xaml::Controls::Expander layOut_;
		winrt::Microsoft::UI::Xaml::Controls::StackPanel panel_;
		winrt::hstring name_;
		std::vector<std::shared_ptr<PropertyInfo>> properties_;
	};

	std::shared_ptr<CategoryInfo> CreateCategory(winrt::hstring const& categoryName, winrt::Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel);
	std::shared_ptr<PropertyInfo> CreatePropertyInfoByNative(Engine::Component::PropertyBase* nativeProp);
}
