#include "pch.h"
#include "DeferredShadingRenderer.h"
#include "RendererBaseHeader.h"
#include "RenderThread.h"

namespace Engine
{
	namespace Renderer
	{
		void RenderThread::Init()
		{
			sceneRenderer = make_unique<DeferredShadingRenderer>();

			RHI::DeviceResourcesUtil::GetInstance().CreateDeviceResources();
			RHI::ShaderObjectManager::GetInstance().LoadShader();
			RHI::DeviceResourcesUtil::GetDeviceResources()->SetOption(RHI::DeviceResources::c_UseXAML);
		}

		void RenderThread::Run()
		{
			activate = true;

			if (worker.joinable())
				return;

			/*게임 쓰레드의 이전 프레임 결과로 렌더링하기. 이전 프레임이 끝나지 않았으면 기다려야함. 해당 조건 통과시에만 렌더링하기.*/

			worker = thread([this]()
				{
					while (activate)
					{
						std::scoped_lock<std::mutex> lock(renderMutex);
						sceneRenderer->Render();												
					}
				});
		}

		void RenderThread::Stop()
		{
			activate = false;
			worker.join();

			auto context = RHI::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			context->ClearState();			
			RHI::DeviceResourcesUtil::GetDeviceResources()->Trim();
		}

		void RenderThread::Exit()
		{
			RHI::DeviceResourcesUtil::GetInstance().ReleaseInstance();
			RHI::ConstantBufferManager::GetInstance().Release();
		}

#pragma region Windows OS dedicated
		void RenderThread::SetSwapChainPanel(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			RHI::DeviceResourcesUtil::GetDeviceResources()->SetSwapChainPanel(swapchainPanelInfo_);
		}
		void RenderThread::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			std::scoped_lock<std::mutex> lock(renderMutex);
			RHI::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapchainPanelInfo_);				
		}
		IDXGISwapChain3* RenderThread::GetSwapChain()
		{			
			return RHI::DeviceResourcesUtil::GetDeviceResources()->GetSwapChain();
		}
#pragma endregion

		void RenderThread::OnWindowSizeChanged(SharedTypes::Size windowSize)
		{			
			std::scoped_lock<std::mutex> lock(renderMutex);
			if (!RHI::DeviceResourcesUtil::GetDeviceResources()->SetLogicalSize(Size(windowSize.Width, windowSize.Height)))
				return;			
		}
	}
}
