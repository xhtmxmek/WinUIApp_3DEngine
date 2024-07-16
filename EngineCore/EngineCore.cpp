#include "pch.h"
#include "GameThread.h"
#include "Renderer/RenderThread.h"
#include "EngineCore.h"
#include "Common/EngineHelper.h"
#include "EngineCoreBuild.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "Level/Actor/ActorManager/ActorManager.h"
#include "System/InputManager.h"
#include <fstream>
#include <sstream>
#include "Common/RuntimeContext.h"

namespace Engine
{
	extern void ExitGame() noexcept;

	shared_ptr<EngineCore> enginePtr_;

	void InitEngine()
	{
		enginePtr_ = make_shared<EngineCore>();
	}

	void ReleaseEngine()
	{
		enginePtr_.reset();
	}

	EngineCore* GetRenderingEngine()
	{
		return enginePtr_.get();
	}

#pragma region Initialize
	void EngineCore::InitializeCoreThread(const SwapchainPanelInfo& swapchainPanelInfo_)
	{
		game_thread = make_unique<GameThread>();
		game_thread->Init();
		render_thread = make_unique<Renderer::RenderThread>();
		render_thread->Init();
		render_thread->SetSwapChainPanel(swapchainPanelInfo_);
	}

	void EngineCore::Initialize(const SwapchainPanelInfo& swapchainPanelInfo_)
	{						
		RuntimeContext::InitialzeRuntimeTable();
		InitializeCoreThread(swapchainPanelInfo_);		
		game_thread->LoadDefaultProject();		
	}

	void EngineCore::UnInitialize()
	{
		game_thread->Exit();
		render_thread->Exit();

		FreeLibrary(ProjectHandle);
	}

	IDXGISwapChain3* EngineCore::GetSwapChain()
	{
		return render_thread->GetSwapChain();
	}
#pragma endregion


#pragma region Frame Update
	void EngineCore::Run()
	{
		game_thread->Run();
		render_thread->Run();
	}

	void EngineCore::Stop()
	{

		game_thread->Stop();
		render_thread->Stop();
	}
#pragma endregion

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
		//gameThread->stop
		render_thread->Stop();
	}

	void EngineCore::OnResuming()
	{		
		game_thread->Run();
		render_thread->Run();
	}

	void EngineCore::OnWindowSizeChanged(SharedTypes::Size windowSize)
	{
		render_thread->OnWindowSizeChanged(windowSize);
	}

	void EngineCore::OnSwapchainXamlChanged(const SwapchainPanelInfo& swapchainPanelInfo_)
	{		
		render_thread->OnSwapchainXamlChanged(swapchainPanelInfo_);
	}

	void EngineCore::KeyProcess(SharedTypes::VirtualKey key, bool isPressed)
	{
		Input::InputManager::GetInstance().SetKeyboardState(key, isPressed);
	}

	void EngineCore::PointerProcess(vector<bool> const& pointerState)
	{
		Input::InputManager::GetInstance().SetMouseState(pointerState);
		//pickingLogic
	}

	void EngineCore::PointerProcess(Vector2i pos)
	{
		Input::InputManager::GetInstance().SetMousePos(pos);
	}

	void EngineCore::PointerProcess(int wheelDelta)
	{
		Input::InputManager::GetInstance().SetWheelDelta(wheelDelta);
	}

	void EngineCore::LoadScriptProject(wstring const& path)
	{
		ProjectHandle = ::LoadLibrary(path.c_str());
		if (ProjectHandle != NULL)
		{
			FreeLibrary(ProjectHandle);
		}
	}

	void EngineCore::PickCheck(Vector2i screenPos, shared_ptr<Level::Actor>& pickedActor)
	{
		//pickedActor = Level::ActorManager::GetInstance().GetActor("MeshTest");
	}

	weak_ptr<Level::Actor> EngineCore::GetActor(int index)
	{
		return Level::SLevel::GetWorld()->GetActor(index);
	}

	weak_ptr<Level::Actor> EngineCore::GetActor(const string& name)
	{
		return Level::SLevel::GetWorld()->GetActor(name);
	}

	size_t EngineCore::GetNumActorList()
	{
		return Level::SLevel::GetWorld()->GetNumActorList();
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

		//https://stackoverflow.com/questions/33082835/windows-10-universal-app-file-directory-access
		//

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
#pragma endregion

}