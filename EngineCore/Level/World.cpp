#include "pch.h"
#include "World.h"
#include "Actor/ActorManager/ActorManager.h"
#include "Actor/Actor.h"
//#include "Actor/Sprite.h"
#include "Renderer/LevelRenderer.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Component/CameraComponent/CameraComponent.h"
#include "Actor/Camera/Camera.h"

using namespace std;
namespace Engine
{
	namespace Level
	{
		World::World()
		{
			PushComponentFunc.reserve(static_cast<int>(Component::SceneComponentType::ComponentType_Max));
			PushComponentFunc.resize(static_cast<int>(Component::SceneComponentType::ComponentType_Max));
			PushComponentFunc[static_cast<int>(Component::SceneComponentType::Drawable)] = std::bind(&World::PushDrawableComponent, this, std::placeholders::_1);
			PushComponentFunc[static_cast<int>(Component::SceneComponentType::Camera)] = std::bind(&World::PushCameraComponent, this, std::placeholders::_1);
			actorManager_ = make_unique<ActorManager>();
			//DrawComponent를 Maximum만큼 정해놓기...
		}

		void World::Init()
		{
			defaultCamera_ = CreateActor<ACamera>("DefaultCamera");
		}
		
		void World::Update(float elapsedTime)
		{
			//스크립트가 init되어있지 않다면 Init. 이미 init 되었으면 update.	
			//스크립트는 일단 상속받는걸로 해보자. 아니면.. callBack을 등록시켜서 스크립트에서 callback을 호출하기.		
			//스크립트에서는 input 정보를 가져옴. 스크립트에서 마우스 로테이션 만큼, 키보드 눌린거에 반응 하여 실행..
			//특정 Value 값에 애니메이션을 줄수 있음.
			//enable인 Actor만 Update.
			//

			for (int i = 0; i < GetNumActorList(); i++)
			{
				auto actor = GetActor(i);
				
				if (actor.expired() == false && actor.lock() != nullptr)
					actor.lock()->Tick(elapsedTime);
			}
				
			//for (const auto& [key, value] : Actors)
			//	value->Tick(elapsedTime);
		}

		void World::Render()
		{
			CheckVisibilityActors();
			Engine::Renderer::LevelRenderer::GetInstance().Render(DrawComponentsThisFrame);
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

			DrawComponentsThisFrame.clear();
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
		void World::PushCameraComponent(const shared_ptr<Component::ComponentBase>& component)
		{			
			cameraComponents_.push_back(shared_ptr(std::static_pointer_cast<Component::CameraComponent>(component)));
		}

		void World::PushDrawableComponent(const shared_ptr<Component::ComponentBase>& component)
		{						
			DrawComponents.push_back((std::static_pointer_cast<Component::DrawableComponent>(component)));
		}
		void World::PushComponent(const shared_ptr<Component::ComponentBase>& component)
		{
			PushComponentFunc[static_cast<int>(component->ComponentType())](component);
		}
	}
}




