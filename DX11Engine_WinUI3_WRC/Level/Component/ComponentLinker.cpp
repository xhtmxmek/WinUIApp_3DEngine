#include "EngineMinimal.h"
#include "ComponentLinker.h"
#include "ComponentBase/ComponentBase.h"
#include "Level/World.h"

namespace Engine
{
	namespace Component
	{
		void ComponentLinkToWorld(Level::World* world, const std::shared_ptr<Component::ComponentBase>& component)
		{			
			//������ Update,Render�� ȣ���Ҽ� �ִٴ� �� ��ü�� ���� �ȵ�.
			//���� �ȿ� �ִ� ���͵��� �ڽŵ��� �θ� World��.			
			component->ComponentType();			
		}

		void ComponentDispatch(const std::shared_ptr<DrawableComponent>& drawableComponent)
		{
			
		}

		void ComponentDispatch(const std::shared_ptr<CameraComponent>& cameraComponent)
		{
		}
	}
}

