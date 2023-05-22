#include "pch.h"
#include "ActorProxy.h"
#include "ActorProxyProcessor.h"
#include "Level/Actor/Actor.h"
#include "Component/ComponentBase/ComponentBase.h"

typedef winrt::EngineInterface_WRC::ActorProxy UIActorProxy;

namespace winrt::EngineInterface_WRC::implementation
{
	ActorProxyProcessor::ActorProxyProcessor()
	{
		actors_ = winrt::single_threaded_observable_vector<winrt::EngineInterface_WRC::ActorProxy>();
	}

	void ActorProxyProcessor::UpdateActorProxyList(const std::unordered_map<std::string, std::shared_ptr<Engine::Level::Actor>>& actorList)
	{
		for (auto& iter : actorList)
		{
			auto nativeActor = iter.second;
			UpdateActorProxy(nativeActor);
		}
	}


	void ActorProxyProcessor::UpdateActorProxy(const std::shared_ptr<Engine::Level::Actor>& actorNative)
	{	
		UIActorProxy actorProxy(winrt::to_hstring(actorNative->GetName()), L"staticMesh");
		for (auto& componentIter : actorNative->Components())
		{
			UpdateActorComponentProxy(componentIter.second);
		}


		for (auto child : actorNative->Children())
		{
			UpdateActorProxy(child);
		}
	}
	void ActorProxyProcessor::UpdateActorComponentProxy(const std::shared_ptr<Engine::Component::ComponentBase>& componentNative)
	{
		ActorComponentProxy componentProxy(winrt::to_hstring(componentNative->Name()));
		for (auto& propertyIter : componentNative->Properties())
		{
			UpdateComponentPropertyProxy(propertyIter); 
		}

		for (auto& child : componentNative->GetChildren())
		{
			UpdateActorComponentProxy(child);
		}
	}
	void ActorProxyProcessor::UpdateComponentPropertyProxy(const std::shared_ptr<Engine::Component::PropertyBase>& propertyNative)
	{
		ComponentPropertyProxy propertyProxy(winrt::to_hstring(propertyNative->Name()));
		//propertyType에 따라 mapping되는 control을 생성한다. map에 type을 key로 담아놓고, 
		//propertyProxy.
	}
	winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorProxy> ActorProxyProcessor::GetActors()
	{
		return actors_;
	}
}
