#include "Renderer/Resource/RHIresource.h"
#include "Renderer/Resource/RenderStates.h"
#include "Renderer/Resource/ConstantBuffer.h"
#include "Renderer/Shader/ShaderObjectManager.h"
#include "Renderer/Resource/deviceContext.h"

namespace Engine
{
	namespace Renderer
	{
		enum class MeshPass
		{
			Depth,
			Base,
			//Velocity,
			Trasnlucency,
			Num,			
		};

		const unsigned int MaxMeshPassNum = static_cast<unsigned int>(MeshPass::Num);
	}
}