#pragma once

namespace Engine
{
	namespace Renderer
	{ 
		namespace RLI
		{
			enum class ShaderType
			{
				Lit,				
				Unlit,
				Cartoon,
				Terrain,
				Max_Type,
			};

			class ShaderObject;

			class ShaderObjectManager
			{

			private:
				std::vector<std::shared_ptr<ShaderObject>> ShaderVector;
				ShaderObjectManager();
				~ShaderObjectManager();

			public:
				//static void CreateInstance();
				//static void ReleaseInstance();
				static ShaderObjectManager& GetInstance()
				{
					static ShaderObjectManager instance;
					return instance;
				}
				void LoadShader();
				std::shared_ptr<ShaderObject> const GetShader(ShaderType eShader);
			};
		}
	}
}

