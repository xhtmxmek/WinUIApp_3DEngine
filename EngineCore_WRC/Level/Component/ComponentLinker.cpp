#include "EngineMinimal.h"
#include "ComponentLinker.h"
#include "ComponentBase/ComponentBase.h"
#include "Level/World.h"
#include "Level/Actor/Actor.h"

namespace Engine
{
	namespace Component
	{
		void ComponentDispatch(Level::Actor* owner, const shared_ptr<Component::ComponentBase>& component)
		{
			owner->GetWorld()->PushComponent(component);
		}

		//void ComponentDispatch(Level::Actor* owner, const std::shared_ptr<CameraComponent>& cameraComponent)
		//{
		//}
	}
}

