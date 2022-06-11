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
		class DrawableComponent;
	}

	namespace Level
	{
		class Actor;		
		//Uncopyable
		class World
		{
		public:			
			//static World& GetInstance()
			//{
			//	static World world;
			//	return world;
			//}

			void PushComponent(const std::shared_ptr<Component::ComponentBase>& component);
			void Update(float elapsedTime);
			void Render();
			//void PushDrawableComponent(std::shared_ptr<Component::DrawableComponent> const& component)
			//{
			//	DrawComponents.push_back(component);
			//}
			//void Push

		private:
			World();
			void CheckVisibilityActors();	//���ü� ����
			std::unordered_map<std::wstring, std::shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 			
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponents;
			std::vector<std::shared_ptr<Component::DrawableComponent>> DrawComponentsThisFrame;
		};
	}
}