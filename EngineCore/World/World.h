#pragma once
#include <vector>
#include <unordered_map>
#include "Common/RuntimeContext.h"
#include "Actor/ActorManager/ActorManager.h"

/*A level is a kind of stage concept. For example, you can think of a world called Yeouido as having 
a level called IFC Mall and a level called National Assembly Building.
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

	namespace World
	{
		class Level;
		class ActorManager;
		class Actor;
		class ACamera;		

		class WorldObject
		{
		public:				
			WorldObject();
			void Init();
			void PushComponent(const shared_ptr<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();

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

			ENGINE_API size_t GetNumActoRHIst()
			{
				return actorManager_->GetNumActoRHIst();
			}
		private:
			unique_ptr<ActorManager> actorManager_;

			//unordered_map<const wchar_t*, shared_ptr<Actor>> Actors; 
			//vector<string> actorNames_; 
			std::weak_ptr<ACamera> defaultCamera_;
			
			vector<weak_ptr<Level>> Levels; 
		};
	}
}