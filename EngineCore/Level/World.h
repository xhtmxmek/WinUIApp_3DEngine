#pragma once
#include <vector>
#include <unordered_map>

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
		class Actor;		
		//Uncopyable
		class World
		{
		public:				
			World();
			void PushComponent(const shared_ptr<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();
			const unordered_map<const wchar_t*, shared_ptr<Actor>> GetActorList();

		private:
			void CheckVisibilityActors();	//���ü� ����			
			void PushCameraComponent(const shared_ptr<Component::ComponentBase>& component);
			void PushDrawableComponent(const shared_ptr<Component::ComponentBase>& component);

			unordered_map<const wchar_t*, shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 			
			vector<shared_ptr<Component::DrawableComponent>> DrawComponents;
			vector<shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
			vector<shared_ptr<Component::CameraComponent>> CameraComponents;

			std::vector<std::function<void(const shared_ptr<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const shared_ptr<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}