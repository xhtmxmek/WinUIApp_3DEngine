#include "pch.h"
#include "DeferredShadingRenderer.h"
//#include "Renderer/Resource/DeviceResources.h"
//#include "Renderer/Shader/ShaderObjectManager.h"
//#include "Renderer/Resource/ConstantBuffer.h"
#include "RenderThread.h"

namespace Engine
{
	namespace Renderer
	{
		void RenderThread::Init()
		{
			sceneRenderer = make_unique<DeferredShadingRenderer>();

			//DX::DeviceResourcesUtil::GetInstance().CreateDeviceResources();
			//Renderer::RLI::ShaderObjectManager::GetInstance().LoadShader();
			//DX::DeviceResourcesUtil::GetDeviceResources()->SetOption(DX::DeviceResources::c_UseXAML);
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

			//auto context = DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			//context->ClearState();			
			//DeviceResourcesUtil::GetDeviceResources()->Trim();
		}

		void RenderThread::Exit()
		{
			//DeviceResourcesUtil::GetInstance().ReleaseInstance();
			//Renderer::RLI::ConstantBufferManager::GetInstance().Release();
		}

#pragma region Windows OS dedicated
		void RenderThread::SetSwapChainPanel(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			//DeviceResourcesUtil::GetDeviceResources()->SetSwapChainPanel(swapchainPanelInfo_);
		}
		void RenderThread::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo_)
		{
			std::scoped_lock<std::mutex> lock(renderMutex);
			//DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapchainPanelInfo_);
			//if (DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapchainPanelInfo_))
			//	CreateWindowSizeDependentResources();
		}
		IDXGISwapChain3* RenderThread::GetSwapChain()
		{
			return nullptr;
			//return DeviceResourcesUtil::GetDeviceResources()->GetSwapChain();
		}
#pragma endregion

		void RenderThread::OnWindowSizeChanged(SharedTypes::Size windowSize)
		{			
			std::scoped_lock<std::mutex> lock(renderMutex);
			//if (!DeviceResourcesUtil::GetDeviceResources()->SetLogicalSize(Size(windowSize.Width, windowSize.Height)))
			//	return;			
		}
	}
}
