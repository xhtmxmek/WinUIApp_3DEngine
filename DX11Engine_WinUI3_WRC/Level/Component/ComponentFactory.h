#pragma once
#include "ComponentTypes.h"
#include "ComponentBase.h"
#include "StaticMeshComponent.h"
#include "SpriteComponent.h"

namespace Engine
{
	namespace Component
	{
		class ComponentBase;

		ComponentBase* CreateComponentPtr(const std::string& name, ActorComponentType type)
		{			
			ComponentBase* newComponent = nullptr;
			switch (type)
			{
			case ActorComponentType::StaticMesh:
				//ComponentBase* component = new StaticMeshComponent();
				break;
			case ActorComponentType::Collision:
				break;
			case ActorComponentType::Camera:
				break;
			case ActorComponentType::Sprite:
				newComponent = new SpriteComponent(name);
				break;
			default:
				break;
			}

			return newComponent;
		}
	}
}