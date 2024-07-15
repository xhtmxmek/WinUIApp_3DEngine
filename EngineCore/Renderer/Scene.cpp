#include "pch.h"
#include "RendererBaseHeader.h"
#include "MeshProcessor.h"
#include "Scene.h"

namespace Engine
{
	namespace Renderer
	{
		void Scene::AddToScene(const shared_ptr<StaticPrimitiveInfo>& primitive)
		{
			static_primitives.push_back(primitive);			
		}
		void Scene::DispatchVisibleDrawCommandList(MeshPass pass)
		{
			if (use_parallel_rendering)
			{				
				//make parallel RLICommand by MeshDrawCommand
				//std::thread
				//draw Count를 쓰레드 갯수로 적절히 나눔.
			}
			else
			{
				for (const auto& drawcommand : visible_drawcommandlist[static_cast<unsigned int>(pass)])
				{	
					//각각의 MeshDrawCommand 순차적으로 submit to pipeline
					DrawUtil::SubmitDrawCommandToPipeline(drawcommand);					
				}				
			}
		}
	}
}

