#pragma once

namespace Engine
{
	namespace World
	{
		class World;
		class Actor;
	}

	namespace Component
	{
		class DrawableComponent;
		class CameraComponent;
		class ComponentBase;

		template<typename T>
		void ComponentLink(const T& component)
		{
			ComponentDispatch(component);
		}

		void ComponentDispatch(Level::Actor* owner, const std::shared_ptr<Engine::Component::ComponentBase>& component);
		//void ComponentDispatch(Level::Actor* owner, shared_ptr<CameraComponent>& component);
	}
}