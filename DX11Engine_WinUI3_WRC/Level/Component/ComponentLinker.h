#pragma once

namespace Engine
{
	namespace Level
	{
		class World;
	}

	namespace Component
	{
		class DrawableComponent;
		class CameraComponent;

		template<typename T>
		void ComponentLink(const T& component)
		{
			ComponentDispatch(component);
		}

		void ComponentDispatch(const std::shared_ptr<DrawableComponent>& component);
		void ComponentDispatch(const std::shared_ptr<CameraComponent>& component);
	}
}