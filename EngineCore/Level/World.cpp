#include "pch.h"
#include "World.h"
#include "Actor/ActorManager/ActorManager.h"
#include "Actor/Actor.h"
//#include "Actor/Sprite.h"
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
			//DrawComponent�� Maximum��ŭ ���س���...
		}

		void World::Init()
		{
			defaultCamera_ = CreateActor<ACamera>("DefaultCamera");
		}
		
		void World::Update(float elapsedTime)
		{
			//��ũ��Ʈ�� init�Ǿ����� �ʴٸ� Init. �̹� init �Ǿ����� update.	
			//��ũ��Ʈ�� �ϴ� ��ӹ޴°ɷ� �غ���. �ƴϸ�.. callBack�� ��Ͻ��Ѽ� ��ũ��Ʈ���� callback�� ȣ���ϱ�.		
			//��ũ��Ʈ������ input ������ ������. ��ũ��Ʈ���� ���콺 �����̼� ��ŭ, Ű���� �����ſ� ���� �Ͽ� ����..
			//Ư�� Value ���� �ִϸ��̼��� �ټ� ����.
			//enable�� Actor�� Update.
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




