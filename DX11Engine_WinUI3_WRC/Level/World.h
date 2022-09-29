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
			void PushComponent(const std::shared_ptr<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();

		private:
			void CheckVisibilityActors();	//���ü� ����			
			void PushCameraComponent(const std::shared_ptr<Component::ComponentBase>& component);
			void PushDrawableComponent(const std::shared_ptr<Component::ComponentBase>& component);

			std::unordered_map<std::wstring, std::shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 			
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponents;
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
			std::vector<std::shared_ptr<Component::CameraComponent>> CameraComponents;
			std::vector<std::shared_ptr<Component::ScriptComponent>> CameraComponents;

			std::vector<std::function<void(const std::shared_ptr<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const std::shared_ptr<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}