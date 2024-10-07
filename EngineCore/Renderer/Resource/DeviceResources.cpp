//
// DeviceResources.cpp - A wrapper for the Direct3D 11 device and swapchain
//                       (requires DirectX 11.3 Runtime)
//


#include "pch.h"
#include "Common/EngineHelper.h"
#include "DeviceResources.h"
#include "Renderer/Resource/RenderStates.h"
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

#pragma region CreateResources
            //void DeviceResources::SetRenderState(const Renderer::RHI::RasterizerState& rs, const Renderer::RHI::SamplerState ss,
            //    const Renderer::RHI::DepthStencilState ds, const Renderer::RHI::BlendState bs)
            //{
            //    m_d3dContext->RSSetState(rs.nativeState_.get());
            //    m_d3dContext->PSSetSamplers(0, 1, ss.nativeState_.addressof());
            //    m_d3dContext->OMSetDepthStencilState(ds.nativeState_.get(), 0);

            //    float blendFactor[4] = { 1,1,1,1 };
            //    m_d3dContext->OMSetBlendState(bs.nativeState_.get(), blendFactor, 0);
            //}

            // This method acquires the first available hardware adapter.
            // If no such adapter can be found, *ppAdapter will be set to nullptr.


            // Sets the color space for the swap chain in order to handle HDR output.
#pragma endregion

#pragma region ValidateDevice
#pragma endregion

        }
    }    
}




