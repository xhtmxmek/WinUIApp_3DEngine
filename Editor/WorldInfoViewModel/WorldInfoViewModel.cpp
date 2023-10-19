#include "pch.h"
#include "WorldInfoViewModel.h"
#include "EngineCore.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "TransformProperty.h"
#include "ActorDetail.h"
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
			if (nativeActor == nullptr)
				continue;

			winrt::Editor::ActorLabel actorLabel(winrt::to_hstring(nativeActor->Name()));
			actorlabels_.Append(actorLabel);
		}
    }

	void WorldInfoViewModel::UpdateSelectedActorDetail(hstring actorName)
	{
		selectedActorDetail_.UpdateActorDeail(actorName);
	}

	void WorldInfoViewModel::ClearSelectedActor()
	{
		selectedActorDetail_.Clear();
	}

	void WorldInfoViewModel::UpdateSelectedComponent(hstring componentName)
	{
		selectedActorDetail_.UpdateSelectedComponent(componentName);
	}
}
