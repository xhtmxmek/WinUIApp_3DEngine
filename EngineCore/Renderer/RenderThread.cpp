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

			RLI::DeviceResourcesUtil::GetInstance().CreateDeviceResources();
			RLI::ShaderObjectManager::GetInstance().LoadShader();
			RLI::DeviceResourcesUtil::GetDeviceResources()->SetOption(RLI::DeviceResources::c_UseXAML);
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

			auto context = RLI::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			context->ClearState();			
			RLI::DeviceResourcesUtil::GetDeviceResources()->Trim();
		}

		void RenderThread::Exit()
		{
			RLI::DeviceResourcesUtil::GetInstance().ReleaseInstance();
			RLI::ConstantBufferManager::GetInstance().Release();
		}

#pragma region Windows OS dedicated
		void RenderThread::SetSwapChainPanel(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			RLI::DeviceResourcesUtil::GetDeviceResources()->SetSwapChainPanel(swapchainPanelInfo_);
		}
		void RenderThread::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			std::scoped_lock<std::mutex> lock(renderMutex);
			RLI::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapchainPanelInfo_);				
		}
		IDXGISwapChain3* RenderThread::GetSwapChain()
		{			
			return RLI::DeviceResourcesUtil::GetDeviceResources()->GetSwapChain();
		}
#pragma endregion

		void RenderThread::OnWindowSizeChanged(SharedTypes::Size windowSize)
		{			
			std::scoped_lock<std::mutex> lock(renderMutex);
			if (!RLI::DeviceResourcesUtil::GetDeviceResources()->SetLogicalSize(Size(windowSize.Width, windowSize.Height)))
				return;			
		}
	}
}
