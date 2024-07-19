#include "Renderer/Resource/RLIresource.h"
#include "Renderer/Resource/RenderStateObjectManager.h"
#include "Renderer/Resource/ConstantBuffer.h"
#include "Renderer/Shader/ShaderObjectManager.h"
#include "Renderer/Resource/DeviceResources.h"

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