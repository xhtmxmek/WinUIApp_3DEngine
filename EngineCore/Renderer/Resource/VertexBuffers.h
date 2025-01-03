#pragma once

#include "RenderResources.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			class VertexBuffer : public RenderResource
			{
			public:
				//virtual void CreateRHI() = 0;
				virtual void ReleaseRHI();
				weak_ptr<RHIBuffer> GetRHI() { return BufferResource; }
			private:
				weak_ptr<RHIBuffer> BufferResource;
			};

			class StaticMeshVertexBuffer : public VertexBuffer
			{
				//VertexBufferData
			};

			class SkeletalMeshVertexBuffer : public VertexBuffer
			{
				//VertexBufferData
			};
		}
	}
}