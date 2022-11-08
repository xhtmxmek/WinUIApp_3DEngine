#include "pch.h"
#include "EngineCore.h"
#include "Common/EngineHelper.h"
#include "Common/DeviceResources.h"
#include "Common/StepTimer.h"
//#include "Common/EngineCriticalSection.h"
//#include "Common/Engine_Scoped_Lock.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "Renderer/LevelRenderer.h"
#include "Level/Actor/ActorManager/ActorManager.h"
#include "System/InputManager.h"
#include "EngineAsset/Texture.h"
#include <fstream>
#include <sstream>
#include "Common/RuntimeContext.h"

namespace Engine
{
	extern void ExitGame() noexcept;

#pragma region Initialize
	//void EngineCore::Initialize(HWND window)
	//{
	//    CreateDeviceDependentResources();
	//    DX::DeviceResourcesUtil::GetDeviceResources()->SetWindow(window, 500, 500);
	//    CreateWindowSizeDependentResources();

	//    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
	//    // e.g. for 60 FPS fixed timestep update logic, call:
	//    /*
	//    m_timer.SetFixedTimeStep(true);
	//    m_timer.SetTargetElapsedSeconds(1.0 / 60);
	//    */
	//}

	void EngineCore::InitializeGlobalObjects()
	{
		m_World = make_shared<Engine::Level::World>();
		Engine::Level::SLevel::SetWorld(m_World);
		Timer = make_unique<Engine::DX::StepTimer>();
		// TODO: Change the timer settings if you want something other than the default variable timestep mode.
		// e.g. for 60 FPS fixed timestep update logic, call:
		/*
		m_timer.SetFixedTimeStep(true);
		m_timer.SetTargetElapsedSeconds(1.0 / 60);
		*/
	}

	void EngineCore::LoadDefaultProject()
	{
		wstring defaultProjFullPath = Path::ProjectDir + L"\\x64\\Debug\\" + Path::ProjectName;
		HMODULE hDll = ::LoadLibrary(defaultProjFullPath.c_str());
		if (hDll != NULL)
		{
			FreeLibrary(hDll);
		}
	}

	void EngineCore::Initialize(const SwapchainPanelInfo& swapChainPanelInfo)
	{
		DX::DeviceResourcesUtil::GetInstance().CreateDeviceResources();
		//DX::DeviceResourcesUtil::GetDeviceResources()->RegisterDeviceNotify(this);
		RuntimeContext::InitialzeRuntimeTable();
		InitializeGlobalObjects();

		Path::InitBasePathes();
		LoadDefaultProject();

		DX::DeviceResourcesUtil::GetDeviceResources()->SetOption(DX::DeviceResources::c_UseXAML);
		CreateDeviceDependentResources();
		DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapChainPanel(swapChainPanelInfo);
		CreateWindowSizeDependentResources();
	}

	void EngineCore::UnInitialize()
	{
		DX::DeviceResourcesUtil::GetInstance().ReleaseInstance();
		Level::SLevel::GetInstance().ReleaseInstance();
		Level::ActorManager::GetInstance().ReleaseInstance();
		EngineAsset::TextureManager::GetInstance().ReleaseInstance();
		FreeLibrary(ProjectHandle);
	}
#pragma endregion


#pragma region Frame Update
	// Executes the basic game loop.
	void EngineCore::Tick()
	{
		Timer->Tick([&]()
			{
				ProcessInput();
				Update(Timer);
			});

		Render();


	}

	// Updates the world.
	void EngineCore::Update(const std::unique_ptr<DX::StepTimer>& timer)
	{
		PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

		float elapsedTime = float(timer->GetElapsedSeconds());

		// TODO: Add your game logic here.
		// Input Update       
		//월드가 스크립트를 가지고 있나? 엔진이 스크립트를 가지고 있나. 월드가 스크립트를 가지고 있는게 맞는거같음.
		//인풋 - > 스크립트 업데이트.
		m_World->Update(elapsedTime);

		PIXEndEvent();
	}

	void EngineCore::StartRenderLoop()
	{
		/*
		쓰레드가 시작된 상태라면 return
		쓰레드가 작업중이라면 joinable은 true이다. 또한 작업을 마쳤더라도 join이 호출되지 않았다면 joinable은 true이다.
		최초 : joinable false. 실행되고 나서 true. 실행 중에 join 호출하면?
		*/
		RenderLoopActivate = true;

		if (RenderLoopThread.joinable())
			return;

		RenderLoopThread = thread([this]()
			{
				while (RenderLoopActivate)
				{
					std::scoped_lock<std::mutex> lock(EngineTickMutex);
					Tick();
				}
			});

		//if (m_renderLoopWorker != nullptr && m_renderLoopWorker.Status() == winrt::Windows::Foundation::AsyncStatus::Started)
		//    return;

		//auto workItemHandler = WorkItemHandler([this, strong_this{ get_strong() }](winrt::Windows::Foundation::IAsyncAction action)
		//    {
		//        while (action.Status() == winrt::Windows::Foundation::AsyncStatus::Started)
		//        {
		//            winrt::DX11Engine_WinUI3_WRC::Engine_Scoped_Lock lock{ m_criticalSection };
		//            Tick();
		//        }
		//    });

		//// 전용인 우선 순위가 높은 백그라운드 스레드에서 작업을 실행합니다.
		//m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
	}

	void EngineCore::StopRenderLoop()
	{
		DX::DeviceResourcesUtil::GetDeviceResources()->Trim();
		RenderLoopActivate = false;
		RenderLoopThread.join();
		//m_renderLoopWorker.Cancel();
	}
#pragma endregion

#pragma region Frame Render
	// Draws the scene.
	void EngineCore::Render()
	{
		// Don't try to render anything before the first Update.
		if (Timer->GetFrameCount() == 0)
		{
			return;
		}

		Clear();

		auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
		PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Render");

		m_World->Render();

		PIXEndEvent(context);

		// Show the new frame.
		PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
		DX::DeviceResourcesUtil::GetDeviceResources()->Present();
		PIXEndEvent();
	}

	// Helper method to clear the back buffers.
	void EngineCore::Clear()
	{
		auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
		PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Clear");

		// Clear the views.
		auto renderTarget = DX::DeviceResourcesUtil::GetDeviceResources()->GetRenderTargetView();
		auto depthStencil = DX::DeviceResourcesUtil::GetDeviceResources()->GetDepthStencilView();

		context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
		context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		context->OMSetRenderTargets(1, &renderTarget, depthStencil);

		// Set the viewport.
		auto viewport = DX::DeviceResourcesUtil::GetDeviceResources()->GetScreenViewport();
		context->RSSetViewports(1, &viewport);

		PIXEndEvent(context);
	}
#pragma endregion 


	// 게임 상태를 업데이트하기 전에 사용자의 모든 입력 처리
	void EngineCore::ProcessInput()
	{
		// TODO: 여기에 프레임 입력 처리별로 추가합니다.
		//m_sceneRenderer->TrackingUpdate(m_pointerLocationX);
	}

#pragma region Message Handlers
	// Message handlers
	void EngineCore::OnActivated()
	{
		// TODO: Game is becoming active window.
	}

	void EngineCore::OnDeactivated()
	{
		// TODO: Game is becoming background window.
	}

	void EngineCore::OnSuspending()
	{
		auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
		context->ClearState();

		DX::DeviceResourcesUtil::GetDeviceResources()->Trim();

		// TODO: Game is being power-suspended.
	}

	void EngineCore::OnResuming()
	{
		Timer->ResetElapsedTime();

		// TODO: Game is being power-resumed.
	}

	void EngineCore::OnWindowSizeChanged(SharedTypes::Size windowSize)
	{
		std::scoped_lock<std::mutex> lock(EngineTickMutex);
		if (!DX::DeviceResourcesUtil::GetDeviceResources()->SetLogicalSize(Size(windowSize.Width, windowSize.Height)))
			return;

		CreateWindowSizeDependentResources();
		
	}

	void EngineCore::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo)
	{
		std::scoped_lock<std::mutex> lock(EngineTickMutex);
		if (DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(swapChainPanelInfo))
			CreateWindowSizeDependentResources();
	}

	//void EngineCore::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
	//{
	//    DX::DeviceResourcesUtil::GetDeviceResources()->SetCurrentOrientation(orientation);
	//    CreateWindowSizeDependentResources();
	//}

	void EngineCore::ValidateDevice()
	{
		DX::DeviceResourcesUtil::GetDeviceResources()->ValidateDevice();
	}

	void EngineCore::KeyProcess(SharedTypes::VirtualKey key, bool isPressed)
	{
		Input::InputManager::GetInstance().SetKeyboardState(key, isPressed);
	}

	void EngineCore::PointerProcess(SharedTypes::PointerButton button, bool isPressed, float delta, Vector2i pos)
	{
		Input::InputManager::GetInstance().SetMouseState(button, isPressed, delta, pos);
		//pickingLogic
	}

	void EngineCore::LoadScriptProject(wstring const& path)
	{
		ProjectHandle = ::LoadLibrary(path.c_str());
		if (ProjectHandle != NULL)
		{
			FreeLibrary(ProjectHandle);
		}
		//로드 시점에 스크립트 프로젝트의 클래스들이 등록됨.
		//런타임 등록을 했으니, 프로젝트 툴을 통하여 등록된 액터를 생성.
		//이후에 해당 스크립트의 Actor를 생성하면 Init이 호출됨.
	}

	void EngineCore::PickCheck(Vector2i screenPos, shared_ptr<Level::Actor>& pickedActor)
	{
		pickedActor = Level::ActorManager::GetInstance().GetActor("MeshTest");
	}

#pragma endregion

#pragma region Direct3D Resources
	// These are the resources that depend on the device.
	bool EngineCore::CreateDeviceDependentResources()
	{
		//auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();        
		// TODO: Initialize device dependent objects here (independent of window size).
		//auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
		//m_spriteBatch = std::make_unique<SpriteBatch>(context);


		//StorageFolder storageFolder = ApplicationData::Current().LocalFolder();
		//winrt::hstring path = storageFolder.Path();
		//path = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();

		//UWP는 샌드박스 식이라 정해진 폴더에만 접근 가능하지만, 우회적인 방법으로 다른곳에도 접근가능.
		//https://stackoverflow.com/questions/33082835/windows-10-universal-app-file-directory-access
		//테스트 되는 리소스들은 엔진에서 제공되는 기본 binaries.
		//

		////WinUi3에서는?
	   // winrt::hstring path = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//winrt::hstring test = L"D:\\StudyDir\\DirectX11Engine_UWP\\cat.png";
		//

		//auto picker = winrt::Windows::Storage::Pickers::FileOpenPicker();        
		//picker.FileTypeFilter().Append(L".jpg");
		//auto file = co_await picker.PickSingleFileAsync();

		//auto file = co_await StorageFile::GetFileFromPathAsync(L"D:\\StudyDir\\DirectX11Engine_UWP\\cat.png");
		//winrt::hstring filePath = file.Path();

		//wchar_t exePath[MAX_PATH] = {};
		//DWORD nc = GetModuleFileName(nullptr, exePath, MAX_PATH);
		//std::wstring strPath(exePath);
		//size_t pos = strPath.rfind(L"\\");

		//if (pos != std::wstring::npos)
		//    strPath = strPath.substr(0, pos);

		//std::wstringstream testStr;
		//testStr << strPath << L"\\test.txt";

		//winrt::hstring path;
		//path = path + L"/Assets/Textures/cat.png";
		//path = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png";
		//com_ptr_nothrow<ID3D11Resource> resource;
		//HRESULT hr = CreateWICTextureFromFile(device, path.c_str(),
		//    //CreateWICTextureFromFile(device, L"Assets/cat.png",
		//    resource.addressof(),
		//    m_texture.put());

		//com_ptr_nothrow<ID3D11Texture2D> cat;
		//DX::ThrowIfFailed(resource.query_to(cat.addressof()));

		//CD3D11_TEXTURE2D_DESC catDesc;
		//cat->GetDesc(&catDesc);

		//m_origin.x = float(catDesc.Width / 2);
		//m_origin.y = float(catDesc.Height / 2);

		return true;
	}

	// Allocate all memory resources that change on a window SizeChanged event.
	void EngineCore::CreateWindowSizeDependentResources()
	{
		// TODO: Initialize windows-size dependent objects here.
		Size outputSize = DX::DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
		float aspectRatio = outputSize.Width / outputSize.Height;
		float fovAngleY = 70.0f * XM_PI / 180.0f;
		//auto size = DX::DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
		//m_screenPos.x = float(outputSize.Width) / 2.f;
		//m_screenPos.y = float(outputSize.Height) / 2.f;
	}

	void EngineCore::OnDeviceLost()
	{
		// TODO: Add Direct3D resource cleanup here.
		//m_spriteBatch.reset();
	}

	void EngineCore::OnDeviceRestored()
	{
		CreateDeviceDependentResources();
		CreateWindowSizeDependentResources();
	}
#pragma endregion

}