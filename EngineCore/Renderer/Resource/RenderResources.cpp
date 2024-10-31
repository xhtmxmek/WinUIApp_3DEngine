#include "pch.h"
#include "RendererBaseHeader.h"
#include "RenderResources.h"

namespace Engine
{
	namespace Renderer
	{
		void RenderResource::InitResource()
		{
			//static State는 staticResource 변수를 초기화 할때  이 함수를 호출함. 자기자신이 heap에 만들어진 변수가 아니므로 shared_ptr로 받을 이유가 없다.			
			//vertexBuffer, Texture와 같은 애셋/메쉬에 종속적인 런타임에 동적으로 생성되는 리소스들역시 등록해야함. 
			_resourceHandle = StaticRenderResources::GetInstance().RegisterResource(this);
		}
		void RenderResource::ReleaseResource()
		{			
			StaticRenderResources::GetInstance().UnRegisterReource(_resourceHandle);
		}

		unsigned int StaticRenderResources::RegisterResource(RenderResource* resource)
		{			
			unsigned int index = 0;
			if (_freeIndexList.empty())
			{
				index = _renderResourceList.size();
				_renderResourceList.emplace_back(resource);
			}
			else
			{
				index = _freeIndexList.size();
				_freeIndexList.pop_back();
				_renderResourceList[index] = resource;
			}
			
			return index;
		}

		void StaticRenderResources::UnRegisterReource(unsigned int resourceHandle)
		{
			_freeIndexList.emplace_back(resourceHandle);
			_renderResourceList[resourceHandle] = nullptr;

		}
		void StaticRenderResources::Clear()
		{
			_freeIndexList.clear();
			_renderResourceList.clear();
		}
		void StaticRenderResources::InitRenderResources()
		{
			for (auto resource : _renderResourceList)
			{
				if (resource != nullptr)
					resource->CreateRHI();
			}
		}
		void StaticRenderResources::ReleaseResources()
		{
			for (auto resource : _renderResourceList)
			{
				if (resource != nullptr)
					resource->ReleaseRHI();
			}
		}
	}
}

