#pragma once
#include <vector>
#include <unordered_map>
#include "Actor/ActorManager/ActorManager.h"

/*
Level�� ���� �ֻ��� ����. Actor�� �������ΰ�?
�ϴ� �����ڷ� �ϰ� Create�� �༮�� ���� �� �پ������� ���丮 Ŭ������ ���� �����
*/

using namespace std;

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
		class Actor;		
		//Uncopyable
		class World
		{
		public:				
			World();
			template<typename T>
			std::shared_ptr<T> SpwanActor(const std::string& name, const Vector3f& pos)
			{				
				auto newActor = Engine::Level::ActorManager::GetInstance().CreateActor<T>(name);
				Actors[name] = std::move(newActor);
				return std::static_pointer_cast<T>(Actors[name]);
			}

			void PushComponent(const shared_ptr<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();
			const std::unordered_map<std::string, shared_ptr<Actor>> GetActorList();

		private:
			void CheckVisibilityActors();	//���ü� ����			
			void PushCameraComponent(const shared_ptr<Component::ComponentBase>& component);
			void PushDrawableComponent(const shared_ptr<Component::ComponentBase>& component);

			unordered_map<std::string, shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 			
			vector<shared_ptr<Component::DrawableComponent>> DrawComponents;
			vector<shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
			vector<shared_ptr<Component::CameraComponent>> CameraComponents;

			std::vector<std::function<void(const shared_ptr<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const shared_ptr<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}