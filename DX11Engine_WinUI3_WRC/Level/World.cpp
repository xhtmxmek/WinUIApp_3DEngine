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

		void World::Update(float elapsedTime)
		{
			//enable인 Actor만 Update.							
			for (const auto& [key, value] : Actors)
				value->Tick(elapsedTime);
		}

		void World::Render()
		{
			//컬링 등...
			CheckVisibilityActors();
			//std::shared_ptr<Engine::Level::ASprite> sprite = Engine::Level::ActorManager::GetInstance().CreateActor<Engine::Level::ASprite>("Hi");
			size_t actorCount = ActorManager::GetInstance().GetNumActorList();			
			Engine::Renderer::LevelRenderer::GetInstance().Render(DrawComponentsThisFrame);
			//int k = 5;
		}

		void World::CheckVisibilityActors()
		{
			//액터가 가지고 있는 DrawComponent들을 넘겨주어야함
			//1. 이곳에서 액터안에 있는 DrawComponent들을 가져와서 검사해서 vector에 집어넣기
			//2. DrawComponent가 생성되는 즉시 DrawComponent로 넘기기
			//DrawActors.clear();
			//DrawActors.reserve(Actors.size());			
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




