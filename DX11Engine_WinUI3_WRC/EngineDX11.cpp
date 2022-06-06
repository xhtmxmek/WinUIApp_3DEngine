#include "EngineMinimal.h"
#include "EngineDX11.h"
#if __has_include("EngineDX11.g.cpp")
#include "EngineDX11.g.cpp"
#endif
#include "Common/EngineHelper.h"
#include "Common/EngineCriticalSection.h"
#include "Common/Engine_Scoped_Lock.h"
#include "Level/World.h"
#include "Renderer/LevelRenderer.h"
#include "Level/Actor/ActorManager.h"
#include <fstream>
#include <sstream>
#include "Common/RuntimeContext.h"
//#include "Level/Actor/Sprite.h"

// Note: Remove this static_assert after copying these generated source files to your project.
// This assertion exists to avoid compiling these generated source files directly.
//static_assert(false, "Do not compile generated C++/WinRT source files directly");

extern void ExitGame() noexcept;

using namespace DirectX;
using namespace DirectX::SimpleMath;
//using namespace winrt;
using namespace winrt::Windows::System::Threading;
//using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;

namespace winrt::DX11Engine_WinUI3_WRC::implementation
{
    EngineDX11::EngineDX11()
        :m_pointerLocationX(0.0f)
    {                
        //DX::DeviceResourcesUtil::GetDeviceResources() = std::make_unique<DX::DeviceResources>();
        DX::DeviceResourcesUtil::GetInstance().CreateDeviceResources();        
        DX::DeviceResourcesUtil::GetDeviceResources()->RegisterDeviceNotify(this);
        m_criticalSection = winrt::make<DX11Engine_WinUI3_WRC::implementation::EngineCriticalSection>();
        Engine::RuntimeContext::InitialzeRuntimeTable();
        m_World = std::make_unique<Engine::Level::World>();        
    }

    EngineDX11::~EngineDX11()
    {        
        DX::DeviceResourcesUtil::GetInstance().ReleaseInstance();
    }

#pragma region Initialize
    //void EngineDX11::Initialize(HWND window)
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

    void EngineDX11::Initialize(Microsoft::UI::Xaml::Controls::SwapChainPanel const& panel)
    {
        DX::DeviceResourcesUtil::GetDeviceResources()->SetOption(DX::DeviceResources::c_UseXAML);
        CreateDeviceDependentResources();
        DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapChainPanel(panel);
        CreateWindowSizeDependentResources();

        //Engine::Level::ActorManager::GetInstance()

        // TODO: Change the timer settings if you want something other than the default variable timestep mode.
        // e.g. for 60 FPS fixed timestep update logic, call:
        /*
        m_timer.SetFixedTimeStep(true);
        m_timer.SetTargetElapsedSeconds(1.0 / 60);
        */
    }

    void EngineDX11::UnInitialize()
    {
        DX::DeviceResourcesUtil::GetDeviceResources().reset();
        m_spriteBatch.reset();
    }
#pragma endregion


#pragma region Frame Update
    // Executes the basic game loop.
    void EngineDX11::Tick()
    {
        m_timer.Tick([&]()
            {
                Update(m_timer);
            });

        Render();

        
    }

    // Updates the world.
    void EngineDX11::Update(DX::StepTimer const& timer)
    {
        PIXBeginEvent(PIX_COLOR_DEFAULT, L"Update");

        float elapsedTime = float(timer.GetElapsedSeconds());

        // TODO: Add your game logic here.        
        m_World->Update(elapsedTime);        

        PIXEndEvent();
    }

    void EngineDX11::StartRenderLoop()
    {
        ProcessInput();
        
        if (m_renderLoopWorker != nullptr && m_renderLoopWorker.Status() == winrt::Windows::Foundation::AsyncStatus::Started)        
            return;        
        
        auto workItemHandler = WorkItemHandler([this, strong_this{ get_strong() }](winrt::Windows::Foundation::IAsyncAction action)
            {                
                while (action.Status() == winrt::Windows::Foundation::AsyncStatus::Started)
                {                                        
                    winrt::DX11Engine_WinUI3_WRC::Engine_Scoped_Lock lock{ m_criticalSection };                    
                    Tick();
                }
            });

        // 전용인 우선 순위가 높은 백그라운드 스레드에서 작업을 실행합니다.
        m_renderLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);
    }

    void EngineDX11::StopRenderLoop()
    {        
        DX::DeviceResourcesUtil::GetDeviceResources()->Trim();
        m_renderLoopWorker.Cancel();                
    }
#pragma endregion

#pragma region Frame Render
    // Draws the scene.
    void EngineDX11::Render()
    {
        // Don't try to render anything before the first Update.
        if (m_timer.GetFrameCount() == 0)
        {
            return;
        }
        
        Clear();

        auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
        PIXBeginEvent(context, PIX_COLOR_DEFAULT, L"Render");


        m_World->Render();        
        // TODO: Add your rendering code here.
        m_spriteBatch->Begin();

        m_spriteBatch->Draw(m_texture.get(), m_screenPos, nullptr,
            Colors::White, 0.f, m_origin);

        m_spriteBatch->End();

        PIXEndEvent(context);

        // Show the new frame.
        PIXBeginEvent(PIX_COLOR_DEFAULT, L"Present");
        DX::DeviceResourcesUtil::GetDeviceResources()->Present();
        PIXEndEvent();
    }

    // Helper method to clear the back buffers.
    void EngineDX11::Clear()
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
    void EngineDX11::ProcessInput()
    {
        // TODO: 여기에 프레임 입력 처리별로 추가합니다.
        //m_sceneRenderer->TrackingUpdate(m_pointerLocationX);
    }

#pragma region Message Handlers
    // Message handlers
    void EngineDX11::OnActivated()
    {
        // TODO: Game is becoming active window.
    }

    void EngineDX11::OnDeactivated()
    {
        // TODO: Game is becoming background window.
    }

    void EngineDX11::OnSuspending()
    {
        auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
        context->ClearState();

        DX::DeviceResourcesUtil::GetDeviceResources()->Trim();

        // TODO: Game is being power-suspended.
    }

    void EngineDX11::OnResuming()
    {
        m_timer.ResetElapsedTime();

        // TODO: Game is being power-resumed.
    }

    void EngineDX11::OnWindowSizeChanged(float width, float height)
    {
        if (!DX::DeviceResourcesUtil::GetDeviceResources()->SetLogicalSize(Windows::Foundation::Size(width, height)))
            return;

        CreateWindowSizeDependentResources();

        // TODO: Game window is being resized.
    }

    void EngineDX11::OnSwapchainXamlChanged(double rasterizationScale, Windows::Foundation::Size size, float compositionScaleX, float compositionScaleY)
    {
        if(DX::DeviceResourcesUtil::GetDeviceResources()->SetSwapchainXamlChanged(rasterizationScale, size, compositionScaleX, compositionScaleY))
            CreateWindowSizeDependentResources();
    }

    void EngineDX11::OnOrientationChanged(winrt::Windows::Graphics::Display::DisplayOrientations const& orientation)
    {
        DX::DeviceResourcesUtil::GetDeviceResources()->SetCurrentOrientation(orientation);
        CreateWindowSizeDependentResources();
    }

    void EngineDX11::ValidateDevice()
    {
        DX::DeviceResourcesUtil::GetDeviceResources()->ValidateDevice();
    }

    // Properties
    void EngineDX11::GetDefaultSize(float& width, float& height) noexcept //const noexcept
    {
        // TODO: Change to desired default window size (note minimum size is 320x200).
        width = 800;
        height = 600;
    }
#pragma endregion

#pragma region Direct3D Resources
    // These are the resources that depend on the device.
    bool EngineDX11::CreateDeviceDependentResources()
    {
        auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();

        // TODO: Initialize device dependent objects here (independent of window size).
        auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
        m_spriteBatch = std::make_unique<SpriteBatch>(context);        


        //StorageFolder storageFolder = ApplicationData::Current().LocalFolder();
        //winrt::hstring path = storageFolder.Path();
        //winrt::hstring path = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();

        //UWP는 샌드박스 식이라 정해진 폴더에만 접근 가능하지만, 우회적인 방법으로 다른곳에도 접근가능.
        //https://stackoverflow.com/questions/33082835/windows-10-universal-app-file-directory-access
        //테스트 되는 리소스들은 엔진에서 제공되는 기본 binaries.
        //

        ////WinUi3에서는?
        winrt::hstring path = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
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
        
        //path = path + L"/Assets/Textures/cat.png";
        path = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png";
        com_ptr_nothrow<ID3D11Resource> resource;
        HRESULT hr = CreateWICTextureFromFile(device, path.c_str(),
            //CreateWICTextureFromFile(device, L"Assets/cat.png",
            resource.addressof(),
            m_texture.put());

        com_ptr_nothrow<ID3D11Texture2D> cat;
        DX::ThrowIfFailed(resource.query_to(cat.addressof()));

        CD3D11_TEXTURE2D_DESC catDesc;
        cat->GetDesc(&catDesc);

        m_origin.x = float(catDesc.Width / 2);
        m_origin.y = float(catDesc.Height / 2);

        return true;
    }

    // Allocate all memory resources that change on a window SizeChanged event.
    void EngineDX11::CreateWindowSizeDependentResources()
    {
        // TODO: Initialize windows-size dependent objects here.
        Windows::Foundation::Size outputSize = DX::DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
        float aspectRatio = outputSize.Width / outputSize.Height;
        float fovAngleY = 70.0f * XM_PI / 180.0f;
        //auto size = DX::DeviceResourcesUtil::GetDeviceResources()->GetOutputSize();
        m_screenPos.x = float(outputSize.Width) / 2.f;
        m_screenPos.y = float(outputSize.Height) / 2.f;
    }

    void EngineDX11::OnDeviceLost()
    {
        // TODO: Add Direct3D resource cleanup here.
        m_spriteBatch.reset();
    }

    void EngineDX11::OnDeviceRestored()
    {
        CreateDeviceDependentResources();

        CreateWindowSizeDependentResources();
    }
#pragma endregion

}
