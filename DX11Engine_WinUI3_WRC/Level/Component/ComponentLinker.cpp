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
			//���Ͱ� ������ �ִ� Level ����
			//������ Update,Render�� ȣ���Ҽ� �ִٴ� �� ��ü�� ���� �ȵ�.
			//���� �ȿ� �ִ� ���͵��� �ڽŵ��� �θ� World��.			
			component->ComponentType();
			world->
		}
	}
}
