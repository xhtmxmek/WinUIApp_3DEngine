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
		class DrawableComponent;
	}

	namespace Level
	{
		class Actor;		
		//Uncopyable
		class World
		{
		public:
			World();
			void Update(float elapsedTime);
			void Render();
			void PushDrawableComponent(std::shared_ptr<Component::DrawableComponent> const& component)
			{
				DrawComponents.push_back(component);
			}

		private:
			void CheckVisibilityActors();	//가시성 판정
			std::unordered_map<std::wstring, std::shared_ptr<Actor>> Actors; //world에는 수많은 액터들이 존재할것이고, 액터가 추가될때 재정렬을 피하기 위해 Hash를 사용헀음. 			
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponents;
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
		};
	}
}