//
// DeviceResources.cpp - A wrapper for the Direct3D 11 device and swapchain
//                       (requires DirectX 11.3 Runtime)
//


#include "pch.h"
#include "DeviceResources.h"
#include "DX11Context.h"
#include "DX12Context.h"
#include "VulkanContext.h"
#include "windows.h"

using namespace std;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

namespace DisplayMetrics
{
    static const bool SupportHighResolutions = false;

    static const float DpiThreshold = 192.0f;
    static const float WidthThreshold = 1920.0f;	
    static const float HeightThreshold = 1080.0f;	
};

// Constants used to calculate screen rotations
namespace ScreenRotation
{
    // 0-degree Z-rotation
    static const XMFLOAT4X4 Rotation0(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 90-degree Z-rotation
    static const XMFLOAT4X4 Rotation90(
        0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 180-degree Z-rotation
    static const XMFLOAT4X4 Rotation180(
        -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // 270-degree Z-rotation
    static const XMFLOAT4X4 Rotation270(
        0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

namespace Engine
{
    namespace Renderer
    {
        namespace RHI
        {
            DeviceResources::DeviceResources(
                SceneColorFormat backBufferFormat,
                SceneColorFormat depthBufferFormat,
                UINT backBufferCount,                
                unsigned int flags) noexcept 
                : _backBufferSize(0.f, 0.f),
                _finalResolution(0.f, 0.f),
                _logicalResolution(0.f, 0.f),
                _nativeOrientation(DisplayOrientation::None),
                _currentOrientation(DisplayOrientation::None),
                _rasterizationScale(0.f),
                _dpi(0.f),
                _compositionScaleX(0.f),
                _compositionScaleY(0.f),
                _effectiveRasterizationScale(0.f),            
                _effectiveCompositionScaleX(0.f),            
                _effectiveCompositionScaleY(0.f)
            {
                CreateDeviceIndependentResources();
                CreateDeviceResources();
            }

#pragma region Initialize
            void DeviceResourcesUtil::CreateDeviceResources()
            {
                if (!_deviceResources)
                {
#ifdef DX11_RHI                    
                    _deviceResources = std::make_shared<DX11Context>();
#elif DX12_RHI
                    _deviceResources = std::make_shared<DX12Context>();
#elif VULKAN_RHI
                    _deviceResources = std::make_shared<VulkanContext>();
#endif						
                }
            }
#pragma endregion   

#pragma region WindowTransform
            void DeviceResources::SetLogicalResolution(SharedTypes::Size logicalSize)
            {
                if (_logicalResolution == logicalSize)
                {
                    // Handle color space settings for HDR
                    //UpdateColorSpace();
                    return;
                }
                _logicalResolution = logicalSize;
                CreateWindowSizeDependentResources();
            }
            
            void DeviceResources::OnWindowTransformChanged(const WindowParam& param)
            {
                SetLogicalResolution(param.ActureSize);
                WindowTransformChanged_Internal(param);
            }
#pragma endregion

        }
    }    
}




