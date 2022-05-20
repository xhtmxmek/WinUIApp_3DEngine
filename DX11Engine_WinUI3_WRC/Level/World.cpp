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
			//enable인 Actor만 Update.							
			for (const auto& [key, value] : Actors)
				value->Tick(elapsedTime);
		}

		void World::Render()
		{
			//컬링 등...
			CheckVisibilityActors();

			Engine::Renderer::LevelRenderer::GetInstance().Render();
		}

		void World::CheckVisibilityActors()
		{
			//액터가 가지고 있는 DrawComponent들을 넘겨주어야함
			//1. 이곳에서 액터안에 있는 DrawComponent들을 가져와서 검사해서 vector에 집어넣기
			//2. DrawComponent가 생성되는 즉시 DrawComponent로 넘기기
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




