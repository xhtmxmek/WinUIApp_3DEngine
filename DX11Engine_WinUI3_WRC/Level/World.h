#pragma once
#include <vector>
#include <unordered_map>

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
		enum SceneComponentType;
	}

	namespace Level
	{
		class Actor;		
		//Uncopyable
		class World
		{
		public:	
			World();
			//static World& GetInstance()
			//{
			//	static World world;
			//	return world;
			//}

			void PushComponent(const std::shared_ptr<Component::ComponentBase>& component)
			{
				//PushComponentFunc[static_cast<int>(component->ComponentType())](component);
			}
			void Update(float elapsedTime);
			void Render();

		private:			
			void CheckVisibilityActors();	//가시성 판정			
			void PushCameraComponent(const std::shared_ptr<Component::ComponentBase>& component);
			void PushDrawableComponent(const std::shared_ptr<Component::ComponentBase>& component);

			std::unordered_map<std::wstring, std::shared_ptr<Actor>> Actors; //world에는 수많은 액터들이 존재할것이고, 액터가 추가될때 재정렬을 피하기 위해 Hash를 사용헀음. 			
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponents;
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
			std::vector<std::shared_ptr<Component::CameraComponent>> CameraComponents;

			//std::vector<std::function<void(const std::shared_ptr<Component::ComponentBase>&)>> PushComponentFunc;
			//std::function<void(const std::shared_ptr<Component::ComponentBase>&)> PushComponentFunc[Component::SceneComponentType::ComponentType_Max];

		};
	}
}