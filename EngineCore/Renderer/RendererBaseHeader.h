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