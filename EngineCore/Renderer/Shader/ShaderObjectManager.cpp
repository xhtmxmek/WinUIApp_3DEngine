#include "pch.h"
#include "ShaderObjectManager.h"
#include "ShaderObject.h"
#include "DefaultShader.h"

namespace Engine
{	
	namespace Renderer
	{
		namespace RHI
		{
			ShaderObjectManager::ShaderObjectManager()
			{
				ShaderVector.clear();
			}

			ShaderObjectManager::~ShaderObjectManager()
			{
				ShaderVector.clear();
			}

			//void ShaderObjectManager::CreateInstance()
			//{
			//	pInstance = new ShaderObjectManager();
			//}

			//void ShaderObjectManager::ReleaseInstance()
			//{
			//	if (pInstance)
			//	{
			//		delete pInstance;
			//		pInstance = nullptr;
			//	}
			//}

			void ShaderObjectManager::LoadShader()
			{
				ShaderVector.reserve(static_cast<int>(ShaderType::Max_Type));
				ShaderVector.resize(static_cast<int>(ShaderType::Max_Type));
	
				//Todo : ShaderObject�� RuntimeŬ������ ��Ͻ�Ű��
				ShaderVector[(int)ShaderType::Lit] = std::shared_ptr<ShaderObject>(new DefaultShader());
				ShaderVector[(int)ShaderType::Unlit] = std::shared_ptr<ShaderObject>(new DefaultShader());
				

				for (int i = (int)ShaderType::Lit; i < (int)ShaderType::Max_Type; i++)
				{					
					if (ShaderVector[i])
					{
						//ShaderVector[i].get()->CreateConstantBuffer();
						ShaderVector[i].get()->CompileShader();
					}
				}

			}


			std::shared_ptr<ShaderObject> const ShaderObjectManager::GetShader(Engine::Renderer::RHI::ShaderType eShader)
			{
				return ShaderVector[(int)eShader];
			}
		}
	}
}

