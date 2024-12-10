#include "pch.h"
#include "Common/EngineHelper.h"
#include "RendererBaseHeader.h"
#include "RHIUtilities.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{

#pragma region Initialize
			void InitRenderResources()
			{
				DeviceContextWrapper::GetInstance().CreateDeviceContext();
				DeviceContextWrapper::GetDeviceContext().lock()->AddOption(RHI::DeviceContext::c_UseXAML);

				StaticRenderResources::GetInstance().InitRenderResources();
				//StaticRenderResource의 종류				
				/*ConstantBufferes
				* CommonTextures
				* SceneTextures
				* VertexBufferes/VertexLayOut
				* IndexBuffers
				* RenderStates
				* ShaderObjectManager
				* 
				*/

				//ShaderObjectManager::GetInstance().LoadShader(); -> renderResource 상속받아서 다시 만들기.
				//ConstantBufferManager::GetInstance().Init(); ->render resource 상속받아서 다시 만들기.
			}

			void PostInitialize()
			{
				DeviceContextWrapper::GetDeviceContext().lock()->PostInitialize();
			}
#pragma endregion

#pragma region Pause/Relase
			void ClearRenderResources()
			{
				auto DeviceContext = DeviceContextWrapper::GetDeviceContext().lock();
				DeviceContext->ClearContext();
			}
			void ReleaseDeviceContext()
			{				
			}
			void ReleaseRenderResources()
			{
				StaticRenderResources::GetInstance().ReleaseResources();
				//ShaderObjectManager::GetInstance().ReleaseShader();
				//RHI::ConstantBufferManager::GetInstance().Release();
				//RHI::ShaderObjectManager::GetInstance().ReleaseShader();

				DeviceContextWrapper::GetInstance().ReleaseInstance();
			}
#pragma endregion


#pragma region RenderStateObject
			shared_ptr<RHIDepthStencilState> CreateRHIDepthStencilState(const DepthStencilDesc& Desc)
			{
				auto DeviceContext = DeviceContextWrapper::GetDeviceContext().lock();
				return DeviceContext->CreateRHIDepthStencilState(Desc);
			}
			void ApplyWindowTransform(const WindowParam& param)
			{
				auto deviceContext = RHI::DeviceContextWrapper::GetDeviceContext().lock();
				deviceContext->OnWindowTransformChanged(param);				
			}
#pragma endregion 
		}
	}
}