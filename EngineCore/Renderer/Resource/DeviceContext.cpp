#include "pch.h"
#include "Common/EngineHelper.h"
#include "DeviceResources.h"
#include "Renderer/Shader/ShaderObjectManager.h"
#include "Renderer/Resource/ConstantBuffer.h"
#include "DeviceContext.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{

#pragma region Initialize
			void Renderer::RHI::InitRenderResources()
			{
				DeviceResourcesUtil::GetInstance().CreateDeviceResources();
				DeviceResourcesUtil::GetDeviceResources().lock()->AddOption(RHI::DeviceResources::c_UseXAML);

				ShaderObjectManager::GetInstance().LoadShader();
				ConstantBufferManager::GetInstance().Init();
			}
#pragma endregion

#pragma region Pause/Relase
			void ClearRenderResources()
			{
				auto deviceResources = DeviceResourcesUtil::GetDeviceResources().lock();
				deviceResources->ClearContext();
			}
			void ReleaseDeviceResources()
			{				
			}
			void ReleaseRenderResources()
			{
				ShaderObjectManager::GetInstance().ReleaseShader();
				RHI::ConstantBufferManager::GetInstance().Release();
				RHI::ShaderObjectManager::GetInstance().ReleaseShader();

				DeviceResourcesUtil::GetInstance().ReleaseInstance();
			}
#pragma endregion


#pragma region RenderStateObject
			weak_ptr<RHIDepthStencilState> CreateRHIDepthStencilState()
			{
				auto deviceResources = DeviceResourcesUtil::GetDeviceResources().lock();
				return deviceResources->CreateRHIDepthStencilState();
			}
#pragma endregion 
		}
	}
}