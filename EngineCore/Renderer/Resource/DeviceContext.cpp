//
// DeviceContext.cpp - A wrapper for the Direct3D 11 device and swapchain
//                       (requires DirectX 11.3 Runtime)
//


#include "pch.h"
#include "RenderStates.h"
#include "DeviceContext.h"
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
            DeviceContext::DeviceContext(
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
                _effectiveRasterizationScale(0.f),
                _dpi(0.f),
                _compositionScale(0.f, 0.f),                                
                _effectiveCompositionScale(0.f, 0.f)
            {
                CreateDeviceIndependentResources();
                CreateDeviceContext();
            }

#pragma region Initialize
            void DeviceContextWrapper::CreateDeviceContext()
            {
                if (!_DeviceContext)
                {
#ifdef DX11_RHI                    
                    _DeviceContext = std::make_shared<DX11Context>();
#elif DX12_RHI
                    _DeviceContext = std::make_shared<DX12Context>();
#elif VULKAN_RHI
                    _DeviceContext = std::make_shared<VulkanContext>();
#endif						
                }
            }
#pragma endregion   

#pragma region WindowTransform
            void DeviceContext::SetLogicalResolution(SharedTypes::Size logicalSize)
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
            
            void DeviceContext::OnWindowTransformChanged(const WindowParam& param)
            {
                //SetLogicalResolution(param.ActureSize);

                bool needChange = false;
                if (_rasterizationScale != GetRasterizationScale())
                {
                    _rasterizationScale = static_cast<float>(param.RasterizationScale);
                    _dpi *= _rasterizationScale;
                    needChange = true;
                }

                if (_logicalResolution != param.ActureSize)
                {
                    _logicalResolution = SharedTypes::Size(param.ActureSize.Width, param.ActureSize.Height);
                    needChange = true;
                }

                if (_compositionScale.Width != param.CompositionScale.x ||
                    _compositionScale.Height != param.CompositionScale.y)
                {
                    _compositionScale.Width = param.CompositionScale.x;
                    _compositionScale.Height = param.CompositionScale.y;
                    needChange = true;
                }

                if (needChange)
                    CreateWindowSizeDependentResources();
            }
#pragma endregion

        }
    }    
}




