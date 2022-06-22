#pragma once

namespace Engine
{
	namespace Level
	{
		class World;
	}

	namespace Component
	{
		class ComponentBase;		

		template<typename T>
		void ComponentLinkToWorld(Level::World* world, const T& component)
		{

		}

		
	}
}