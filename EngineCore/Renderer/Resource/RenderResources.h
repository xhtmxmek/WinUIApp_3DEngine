#pragma once

/*
* RenderResource :ex)VertexBuffer, RenderState, ConstantBuffer, ClassRenderTarget, Texture...
* RenderResource is managed in static class. when engine initialize, RenderResources are registered. when engine exit, renderResources is released.
* RenderResource has *
*/

namespace Engine
{
	namespace Renderer
	{
		class RenderResource
		{
		public:
			virtual void CreateRHI() = 0;
			virtual void ReleaseRHI() = 0;			
			void InitResource();
			void ReleaseResource();
		private:
			unsigned int _resourceHandle;
		};

		class StaticRenderResources
		{
		public:
			static StaticRenderResources& GetInstance()
			{
				static StaticRenderResources instance;
				return instance;
			}

			/*
			* 1.PreRegisteredRenderResource
			* -SceneTexture : init Engine / release Engine.
			-ConstantBuffer : init Engine / Release Engine.
			-RenderStates : init Engine / Release Engine.
			-CustomRenderTarget : dynaimc Init / dynamic Release.(by Index or handle acquired from RenderReources when resource generated)
			-CustomConstantBuffer : dynaimc Init / dynamic Release.(by Index or handle acquired from RenderReources when resource generated)
			-CustomTexture : dynaimc Init / dynamic Release.(by Index or handle acquired from RenderReources when resource generated)
			*/

			unsigned int RegisterResource(RenderResource* resource);
			void UnRegisterReource(unsigned int resourceHandle);
			void Clear();
			void InitRenderResources();
			void ReleaseResources();
		private:
			StaticRenderResources() = default;
			StaticRenderResources(const StaticRenderResources&) = delete;
		private:
			std::vector<RenderResource*> _renderResourceList;
			std::vector<unsigned int> _freeIndexList;
		};
	}
}
