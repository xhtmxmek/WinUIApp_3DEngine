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
			void PushComponent(const SharedPointer<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();

		private:
			void CheckVisibilityActors();	//���ü� ����			
			void PushCameraComponent(const SharedPointer<Component::ComponentBase>& component);
			void PushDrawableComponent(const SharedPointer<Component::ComponentBase>& component);

			HashMap<const wchar_t*, SharedPointer<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 			
			Vector<SharedPointer<Component::DrawableComponent>> DrawComponents;
			Vector<SharedPointer<Component::DrawableComponent>> DrawComponentsThisFrame;
			Vector<SharedPointer<Component::CameraComponent>> CameraComponents;

			std::vector<std::function<void(const SharedPointer<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const SharedPointer<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}