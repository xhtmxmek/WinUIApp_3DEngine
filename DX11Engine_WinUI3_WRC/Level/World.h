#pragma once
#include <vector>
#include <unordered_map>

/*
Level�� ���� �ֻ��� ����. Actor�� �������ΰ�?
�ϴ� �����ڷ� �ϰ� Create�� �༮�� ���� �� �پ������� ���丮 Ŭ������ ���� �����
*/

namespace Engine
{
	namespace Level
	{
		class Actor;
		class DrawableComponent;

		//Uncopyable
		class World
		{
		public:
			World();
			void Update(float elapsedTime);
			void Render();

		private:
			void CheckVisibilityActors();	//���ü� ����
			std::unordered_map<std::wstring, std::shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 			
			std::vector<std::shared_ptr<DrawableComponent>> DrawComponents;
			std::vector<std::shared_ptr<DrawableComponent>> DrawComponentsThisFrame;
		};
	}
}