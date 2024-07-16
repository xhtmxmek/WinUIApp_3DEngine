#include "pch.h"
#include "DeferredShadingRenderer.h"
#include "Renderer/Resource/DeviceResources.h"
#include "Renderer/Shader/ShaderObjectManager.h"
#include "Renderer/Resource/ConstantBuffer.h"
#include "RenderThread.h"

namespace Engine
{
	namespace Renderer
	{
		void RenderThread::Init()
		{
			scene_renderer = make_unique<DeferredShadingRenderer>();

			DX::DeviceResourcesUtil::GetInstance().CreateDeviceResources();
			Renderer::RLI::ShaderObjectManager::GetInstance().LoadShader();

			DX::DeviceResourcesUtil::GetDeviceResources()->SetOption(DX::DeviceResources::c_UseXAML);
		}

		void RenderThread::Run()
		{
			activate = true;

			if (worker.joinable())
				return;

			/*게임 쓰레드의 이전 프레임 결과로 렌더링하기. 해당 조건 통과시에만 렌더링하기.*/

			worker = thread([this]()
				{
					while (activate)
					{
						std::scoped_lock<std::mutex> lock(renderMutex);
						scene_renderer->Render();												
					}
				});
		}

		void RenderThread::Stop()
		{
			activate = false;
			worker.join();

			auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			context->ClearState();			
			DX::DeviceResourcesUtil::GetDeviceResources()->Trim();
		}

		void RenderThread::Exit()
		{
			DX::DeviceResourcesUtil::GetInstance().ReleaseInstance();
			Renderer::RLI::ConstantBufferManager::GetInstance().Release();
		}

#pragma region Windows OS dedicated
		void RenderThread::SetSwapChainPanel(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapChainPanel(swapchainPanelInfo_);
		}
		void RenderThread::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			std::scoped_lock<std::mutex> lock(renderMutex);
			DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapchainPanelInfo_);
			//if (DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapchainPanelInfo_))
			//	CreateWindowSizeDependentResources();
		}
		IDXGISwapChain3* RenderThread::GetSwapChain()
		{
			return DX::DeviceResourcesUtil::GetDeviceResources()->GetSwapChain();
		}
#pragma endregion

		void RenderThread::OnWindowSizeChanged(SharedTypes::Size windowSize)
		{			
			std::scoped_lock<std::mutex> lock(renderMutex);
			if (!DX::DeviceResourcesUtil::GetDeviceResources()->SetLogicalSize(Size(windowSize.Width, windowSize.Height)))
				return;			
		}
	}
}
