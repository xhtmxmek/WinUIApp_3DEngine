#pragma once


namespace Engine
{	
	namespace Level
	{
		class Actor;
	}

	namespace Component
	{
		class ComponentBase;
		class PropertyBase;
	}
}

namespace winrt::EngineInterface_WRC::implementation
{
	class ActorProxyProcessor
	{
	public:
		ActorProxyProcessor();
		
		void UpdateActorProxyList(const std::unordered_map<std::string, std::shared_ptr<Engine::Level::Actor>>& actorList);
		void UpdateActorProxy(const std::shared_ptr<Engine::Level::Actor>& actorNative);
		void UpdateActorComponentProxy(const std::shared_ptr<Engine::Component::ComponentBase>& componentNative);
		void UpdateComponentPropertyProxy(const std::shared_ptr<Engine::Component::PropertyBase>& propertyNative);

		winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorProxy> GetActors();
	private:
		//winrt::Windows::Foundation::Collections::IMap<hstring, winrt::EngineInterface_WRC::ActorProxy> actors;
		winrt::Windows::Foundation::Collections::IObservableVector<winrt::EngineInterface_WRC::ActorProxy> actors_;
	};
}