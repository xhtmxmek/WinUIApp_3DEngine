#include "pch.h"
#include "World.h"
#include "Actor/Actor.h"
#include "Renderer/LevelRenderer.h"
#include "Component/ComponentBase.h"

using namespace std;
namespace Engine
{
	namespace Level
	{
		World::World()
		{
			Actors.clear();			
		}

		void World::Update(float elapsedTime)
		{
			//enable�� Actor�� Update.							
			for (const auto& [key, value] : Actors)
				value->Tick(elapsedTime);
		}

		void World::Render()
		{
			//�ø� ��...
			CheckVisibilityActors();

			Engine::Renderer::LevelRenderer::GetInstance().Render();
		}

		void World::CheckVisibilityActors()
		{
			//���Ͱ� ������ �ִ� DrawComponent���� �Ѱ��־����
			//1. �̰����� ���;ȿ� �ִ� DrawComponent���� �����ͼ� �˻��ؼ� vector�� ����ֱ�
			//2. DrawComponent�� �����Ǵ� ��� DrawComponent�� �ѱ��
			//DrawActors.clear();
			//DrawActors.reserve(Actors.size());
			DrawableComponent test;
			for (const auto& elements : DrawComponents)
			{
				elements->
			}
				//is visible?
				//
				//frustom culling

				//occlusion culling
		}
	}
}




