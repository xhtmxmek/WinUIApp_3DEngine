#include "EngineMinimal.h"
#include "World.h"
#include "Actor/ActorManager.h"
#include "Actor/Actor.h"
//#include "Actor/Sprite.h"
#include "Renderer/LevelRenderer.h"
#include "Component/ComponentBase.h"

using namespace std;
namespace Engine
{
	namespace Level
	{
		World::World()
		{
			Actors.clear();			
		}

		void World::PushComponent(const std::shared_ptr<Component::ComponentBase>& component)
		{
		}

		void World::Update(float elapsedTime)
		{
			//enable�� Actor�� Update.							
			for (const auto& [key, value] : Actors)
				value->Tick(elapsedTime);
		}

		void World::Render()
		{
			//�ø� ��...
			CheckVisibilityActors();			
			size_t actorCount = ActorManager::GetInstance().GetNumActorList();			
			Engine::Renderer::LevelRenderer::GetInstance().Render(DrawComponentsThisFrame);
			//int k = 5;
		}

		void World::CheckVisibilityActors()
		{
			//���Ͱ� ������ �ִ� DrawComponent���� �Ѱ��־����
			//1. �̰����� ���;ȿ� �ִ� DrawComponent���� �����ͼ� �˻��ؼ� vector�� ����ֱ�
			//2. DrawComponent�� �����Ǵ� ��� DrawComponent�� �ѱ��
			//DrawActors.clear();
			//DrawActors.reserve(Actors.size());			
			//���ʹ� �������� drawComponent�� ����������. ���⼭ ���Ͱ� �������ִ� ������Ʋ�� ���� �˻��ؾ��ϳ�? �ƴϸ�
			//
			DrawComponentsThisFrame.reserve(DrawComponents.size());
			for (const auto& elements : DrawComponents)
			{
				//is visible?
				if (!elements->IsVisible())
					continue;
				//frustom culling	
				//occlusion culling
				DrawComponentsThisFrame.push_back(elements);				
			}
		}
	}
}




