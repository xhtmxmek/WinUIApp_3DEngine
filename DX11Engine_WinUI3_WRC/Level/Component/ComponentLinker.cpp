#include "EngineMinimal.h"
#include "ComponentLinker.h"
#include "ComponentBase.h"
#include "Level/World.h"

namespace Engine
{
	namespace Component
	{
		void ComponentLinkToWorld(Level::World* world, const std::shared_ptr<Component::ComponentBase>& component)
		{
			//액터가 가지고 있는 Level 포인
			//월드의 Update,Render를 호출할수 있다는 것 자체가 맘에 안듬.
			//레벨 안에 있는 액터들은 자신들의 부모가 World임.			
			component->ComponentType();
			world->
		}
	}
}

