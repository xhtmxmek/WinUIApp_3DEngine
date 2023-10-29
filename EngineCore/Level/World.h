#pragma once
#include <vector>
#include <unordered_map>
#include "Common/RuntimeContext.h"
#include "Actor/ActorManager/ActorManager.h"


/*
Level�� ���� �ֻ��� ����. Actor�� �������ΰ�?
�ϴ� �����ڷ� �ϰ� Create�� �༮�� ���� �� �پ������� ���丮 Ŭ������ ���� �����
*/

namespace Engine
{
	namespace Component
	{
		class ComponentBase;
		class DrawableComponent;
		class CameraComponent;
		enum class SceneComponentType;
	}

	namespace Level
	{
		class ActorManager;
		class Actor;		
		//Uncopyable
		class World
		{
		public:				
			World();
			void PushComponent(const shared_ptr<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();

			//���������� ������ �̸��� �����;���. ������ Ű���� ���� �ʿ� ����.
			/*
			* ������ü�� ������ UID�� �������Ѵ�. �ߺ��� ID�� ������ ���.
			* ��� �ּҰ� ������ ���̱� �ϴ�.
			*/
			ENGINE_API weak_ptr<Actor> GetActor(const string& name)
			{
				return actorManager_->GetActor(name);
			}

			ENGINE_API weak_ptr<Actor> GetActor(unsigned int index)
			{
				return actorManager_->GetActor(index);
			}

			template<typename T>
			std::weak_ptr<T> CreateActor(const std::string& name)
			{
				return actorManager_->CreateActor<T>(name);
			}

			ENGINE_API size_t GetNumActorList()
			{
				return actorManager_->GetNumActorList();
			}


		private:
			void CheckVisibilityActors();	//���ü� ����			
			void PushCameraComponent(const shared_ptr<Component::ComponentBase>& component);
			void PushDrawableComponent(const shared_ptr<Component::ComponentBase>& component);

		private:
			unique_ptr<ActorManager> actorManager_;

			//unordered_map<const wchar_t*, shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������.
			//vector<string> actorNames_; 

			vector<shared_ptr<Component::DrawableComponent>> DrawComponents;
			vector<shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
			vector<shared_ptr<Component::CameraComponent>> CameraComponents;

			std::vector<std::function<void(const shared_ptr<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const shared_ptr<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}