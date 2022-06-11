#pragma once

namespace Engine
{
	namespace Component
	{
		class ComponentBase;		

		void ComponentLinkToWorld(Level::World* world, const std::shared_ptr<Component::ComponentBase>& component);
	}
}