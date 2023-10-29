#pragma once
#include <vector>
#include <unordered_map>
#include "Common/RuntimeContext.h"
#include "Actor/ActorManager/ActorManager.h"


/*
Level의 가장 최상위 구조. Actor의 생산자인가?
일단 생산자로 하고 Create할 녀석이 좀만 더 다양해지면 팩토리 클래스를 따로 만들기
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

			//순차적으로 액터의 이름을 가져와야함. 액터의 키값은 전혀 필요 없음.
			/*
			* 액터자체는 고유한 UID를 가져야한다. 중복된 ID를 가지면 노우.
			* 사실 주소가 고유한 값이긴 하다.
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
			void CheckVisibilityActors();	//가시성 판정			
			void PushCameraComponent(const shared_ptr<Component::ComponentBase>& component);
			void PushDrawableComponent(const shared_ptr<Component::ComponentBase>& component);

		private:
			unique_ptr<ActorManager> actorManager_;

			//unordered_map<const wchar_t*, shared_ptr<Actor>> Actors; //world에는 수많은 액터들이 존재할것이고, 액터가 추가될때 재정렬을 피하기 위해 Hash를 사용헀음.
			//vector<string> actorNames_; 

			vector<shared_ptr<Component::DrawableComponent>> DrawComponents;
			vector<shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
			vector<shared_ptr<Component::CameraComponent>> CameraComponents;

			std::vector<std::function<void(const shared_ptr<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const shared_ptr<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}