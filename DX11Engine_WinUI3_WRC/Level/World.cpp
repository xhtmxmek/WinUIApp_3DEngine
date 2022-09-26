#include "EngineMinimal.h"
#include "World.h"
#include "Actor/ActorManager/ActorManager.h"
#include "Actor/Actor.h"
//#include "Actor/Sprite.h"
#include "Renderer/LevelRenderer.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Component/CameraComponent/CameraComponent.h"

using namespace std;
namespace Engine
{
	namespace Level
	{
		World::World()
		{
			Actors.clear();			
			PushComponentFunc.reserve(static_cast<int>(Component::SceneComponentType::ComponentType_Max));
			PushComponentFunc.resize(static_cast<int>(Component::SceneComponentType::ComponentType_Max));
			PushComponentFunc[static_cast<int>(Component::SceneComponentType::Drawable)] = std::bind(&World::PushDrawableComponent, this, std::placeholders::_1);
			PushComponentFunc[static_cast<int>(Component::SceneComponentType::Camera)] = std::bind(&World::PushCameraComponent, this, std::placeholders::_1);

			//DrawComponent를 Maximum만큼 정해놓기...
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
			//액터는 여러개의 drawComponent를 가질수있음. 여기서 액터가 가지고있는 컴포넌틀를 전부 검사해야하나? 아니면
			//

			size_t test = ActorManager::GetInstance().GetNumActorList();
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
		void World::PushCameraComponent(const std::shared_ptr<Component::ComponentBase>& component)
		{
			CameraComponents.push_back(std::static_pointer_cast<Component::CameraComponent>(component));
		}

		void World::PushDrawableComponent(const shared_ptr<Component::ComponentBase>& component)
		{			
			DrawComponents.push_back(std::static_pointer_cast<Component::DrawableComponent>(component));
		}
		void World::PushComponent(const std::shared_ptr<Component::ComponentBase>& component)
		{
			PushComponentFunc[static_cast<int>(component->ComponentType())](component);
		}
	}
}




