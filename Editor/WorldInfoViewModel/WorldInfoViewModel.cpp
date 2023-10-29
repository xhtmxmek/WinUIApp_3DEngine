#include "pch.h"
#include "WorldInfoViewModel.h"
#include "EngineCore.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "ActorDetail.h"
#include "Common/RuntimeContext.h"
#include "WorldInfoViewModel.g.cpp"


namespace winrt::Editor::implementation
{
    WorldInfoViewModel::WorldInfoViewModel()
    {
		actorlabels_ = winrt::single_threaded_observable_vector<Editor::ActorLabel>();
		selectedActorDetail_ = winrt::make<Editor::implementation::ActorDetail>(L"");
		selectedActorDetail_.Visible(Microsoft::UI::Xaml::Visibility::Collapsed);
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Editor::ActorLabel> WorldInfoViewModel::ActorLabels()
    {
        return actorlabels_;
    }

	winrt::Editor::ActorDetail WorldInfoViewModel::SelectedActorDetail()
    {
        return selectedActorDetail_;
    }

    void WorldInfoViewModel::UpdateWorldInfoProxy()
    {
		auto engine = Engine::GetRenderingEngine();
		for (int index = 0; index < engine->GetNumActorList(); index++)
		{
			auto nativeActor = engine->GetActor(index);
			if (nativeActor.expired())
				continue;

			if (nativeActor.lock() == nullptr)
				continue;

			winrt::Editor::ActorLabel actorLabel(winrt::to_hstring(nativeActor.lock()->Name()),
				winrt::to_hstring(nativeActor.lock()->ImplClassName()));
			actorlabels_.Append(actorLabel);			
			OutlinerComment(to_hstring(actorlabels_.Size()) + L" Actors Loaded");
		}
    }

	void WorldInfoViewModel::UpdateSelectedActorDetail(hstring actorName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
	{
		selectedActorDetail_.UpdateActorDeail(actorName, detailPanel);		
	}

	void WorldInfoViewModel::ClearSelectedActor(Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
	{
		selectedActorDetail_.Clear(detailPanel);
		//selectedActorDetail_ = nullptr;
	}

	void WorldInfoViewModel::UpdateSelectedComponent(hstring componentName, Microsoft::UI::Xaml::Controls::StackPanel const& detailPanel)
	{
		selectedActorDetail_.UpdateSelectedComponent(componentName, detailPanel);
	}
	hstring WorldInfoViewModel::OutlinerComment()
	{
		return outlinerComment_;
	}
	void WorldInfoViewModel::OutlinerComment(hstring const& value)
	{
		if (outlinerComment_ != value)
		{
			outlinerComment_ = value;
			propertyChanged_(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"OutlinerComment" });
		}
	}
}
