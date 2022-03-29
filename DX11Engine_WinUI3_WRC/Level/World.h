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
		class DrawAbleActor;

		//Uncopyable
		class World
		{
		public:
			World();
			void Update(float fElapsedTime);
			void Render();
			std::shared_ptr<Actor> CreateActor(const std::string& name, UINT layerMask);

		private:
			void CheckVisibilityActors();	//���ü� ����
			std::unordered_map<std::wstring, std::shared_ptr<Actor>> Actors; //world���� ������ ���͵��� �����Ұ��̰�, ���Ͱ� �߰��ɶ� �������� ���ϱ� ���� Hash�� �������. 
			std::vector<std::shared_ptr<DrawAbleActor>> DrawActors; 
		};
	}
}