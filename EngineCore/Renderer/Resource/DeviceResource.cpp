//
// DeviceResources.cpp - A wrapper for the Direct3D 11 device and swapchain
//                       (requires DirectX 11.3 Runtime)
//


#include "pch.h"
#include "Common/EngineHelper.h"
#include "DeviceResources.h"
#include "Renderer/Resource/RenderStates.h"
#include "windows.h"

using namespace D2D1;
using namespace DirectX;
using namespace Engine::DX;
using namespace std;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

namespace DisplayMetrics
{
    // ���ػ� ���÷��̴� �������ϴ� �� ���� GPU �� ���͸� ������ �ʿ��� �� �ֽ��ϴ�.
    // ���� ��� ���ػ� �޴����� ���ӿ��� ��ȭ���� �ʴ� 60�������� �������Ϸ���
    // ��� ª�� ���͸� �������� ���� ������ �߻��� �� �ֽ��ϴ�.
    // ��� �÷��� �� �� ���Ϳ��� ��ȭ���� �������ϴ� ������
    // �����ϰ� ������ �մϴ�.
    static const bool SupportHighResolutions = false;

    // �����ػ󵵡� ���÷��̸� �����ϴ� �⺻ �Ӱ谪�Դϴ�. �Ӱ谪�� �ʰ��ϰų�
    // SupportHighResolutions�� false�� ��� ũ�Ⱑ 50%��
    //�پ��ϴ�.
    static const float DpiThreshold = 192.0f;		// ǥ�� ����ũ�� ���÷����� 200%�Դϴ�.
    static const float WidthThreshold = 1920.0f;	// �ʺ� 1080p�Դϴ�.
    static const float HeightThreshold = 1080.0f;	// ���̰� 1080p�Դϴ�.
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
                unsigned int flags) noexcept :
                m_screenViewport{},
                m_backBufferFormat(backBufferFormat),
                m_depthBufferFormat(depthBufferFormat),
                m_backBufferCount(backBufferCount),
                m_d3dMinFeatureLevel(minFeatureLevel),
                m_window(nullptr),
                m_d3dFeatureLevel(D3D_FEATURE_LEVEL_9_1),
                m_rotation(DXGI_MODE_ROTATION_IDENTITY),
                m_dxgiFactoryFlags(0),
                m_outputSize(),
                m_logicalSize(),
                m_RasterizationScale(-1.0),
                m_effectiveRasterizationScale(-1.0f),
                m_orientationTransform3D(ScreenRotation::Rotation0),
                m_colorSpace(DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709),
                m_options(flags),
                m_deviceNotify(nullptr)
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

#pragma region WindowSet
            
#pragma endregion

#pragma region ValidateDevice
#ifdef WIN_APPS_SDK
            bool DeviceResources::SetSwapchainXamlChanged(const SwapchainPanelInfo& swapChainPanelInfo)
            {
                bool needChange = false;
                if (static_cast<float>(swapChainPanelInfo.RasterizationScale) != _rasterizationScale)
                {
                    _rasterizationScale = static_cast<float>(swapChainPanelInfo.RasterizationScale);
                    _dpi *= _rasterizationScale;
                    _d2dContext->SetDpi(m_dpi, m_dpi);
                    needChange = true;
                }

                if (_logicalResolution != swapChainPanelInfo.ActureSize)
                {
                    _logicalResolution = SharedTypes::Size(swapChainPanelInfo.ActureSize.Width, swapChainPanelInfo.ActureSize.Height);
                    needChange = true;
                }

                if (_compositionScaleX != swapChainPanelInfo.CompositionScale.x ||
                    _compositionScaleY != swapChainPanelInfo.CompositionScale.y)
                {
                    _compositionScaleX = swapChainPanelInfo.CompositionScale.x;
                    _compositionScaleY = swapChainPanelInfo.CompositionScale.y;
                    needChange = true;
                }

                if (needChange)
                    CreateWindowSizeDependentResources();

                return needChange;
            }

            void DeviceResources::SetCurrentOrientation(Engine::DisplayOrientation currentOrientation)
            {
                if (m_currentOrientation != currentOrientation)
                {
                    m_currentOrientation = currentOrientation;
                    CreateWindowSizeDependentResources();
                }
            }

            // �� �޼���� CompositionScaleChanged �̺�Ʈ�� �̺�Ʈ ó���⿡�� ȣ��˴ϴ�.
            void DeviceResources::SetCompositionScale(float compositionScaleX, float compositionScaleY)
            {
                if (m_options & c_UseXAML)
                {
                    if (m_compositionScaleX != compositionScaleX ||
                        m_compositionScaleY != compositionScaleY)
                    {
                        m_compositionScaleX = compositionScaleX;
                        m_compositionScaleY = compositionScaleY;
                        CreateWindowSizeDependentResources();
                    }
                }
            }

            DXGI_MODE_ROTATION DeviceResources::ComputeDisplayRotation()
            {
                DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

                // ����: NativeOrientation�� DisplayOrientations �������� �ٸ� ���� �����ϴ���
                // Landscape �Ǵ� Portrait�� �� �� �ֽ��ϴ�.
                //switch (m_nativeOrientation)
                //{
                //case DisplayOrientations::Landscape:
                //    switch (m_currentOrientation)
                //    {
                //    case DisplayOrientations::Landscape:
                //        rotation = DXGI_MODE_ROTATION_IDENTITY;
                //        break;

                //    case DisplayOrientations::Portrait:
                //        rotation = DXGI_MODE_ROTATION_ROTATE270;
                //        break;

                //    case DisplayOrientations::LandscapeFlipped:
                //        rotation = DXGI_MODE_ROTATION_ROTATE180;
                //        break;

                //    case DisplayOrientations::PortraitFlipped:
                //        rotation = DXGI_MODE_ROTATION_ROTATE90;
                //        break;
                //    }
                //    break;

                //case DisplayOrientations::Portrait:
                //    switch (m_currentOrientation)
                //    {
                //    case DisplayOrientations::Landscape:
                //        rotation = DXGI_MODE_ROTATION_ROTATE90;
                //        break;

                //    case DisplayOrientations::Portrait:
                //        rotation = DXGI_MODE_ROTATION_IDENTITY;
                //        break;

                //    case DisplayOrientations::LandscapeFlipped:
                //        rotation = DXGI_MODE_ROTATION_ROTATE270;
                //        break;

                //    case DisplayOrientations::PortraitFlipped:
                //        rotation = DXGI_MODE_ROTATION_ROTATE180;
                //        break;
                //    }
                //    break;
                //}
                return rotation;
            }

            void DeviceResources::UpdateRenderTargetSize()
            {
                m_effectiveRasterizationScale = m_RasterizationScale;
                if (m_options & c_UseXAML)
                {
                    m_effectiveCompositionScaleX = m_compositionScaleX;
                    m_effectiveCompositionScaleY = m_compositionScaleY;
                }

                // ���ػ� ����̽����� ���͸� ������ �����Ϸ��� �� ���� ������ ������� �������ϰ�
                // ����� ǥ���� �� GPU���� ����� ũ�⸦ ������ �� �ֵ��� ����մϴ�.
                if (!DisplayMetrics::SupportHighResolutions && m_RasterizationScale > DisplayMetrics::DpiThreshold)
                {
                    float width = m_logicalSize.Width * m_RasterizationScale;
                    float height = m_logicalSize.Height * m_RasterizationScale;

                    // ����̽��� ���� �����̸� ���̰� �ʺ񺸴� Ů�ϴ�. ū ġ����
                    // �ʺ� �Ӱ谪�� ���ϰ� ���� ġ����
                    // ���� �Ӱ谪�� ���մϴ�.
                    if (max(width, height) > DisplayMetrics::WidthThreshold && min(width, height) > DisplayMetrics::HeightThreshold)
                    {
                        // ���� ũ�⸦ �����ϱ� ���� ��ȿ DPI�� �����մϴ�. ��� ũ��� ������� �ʽ��ϴ�.
                        m_effectiveRasterizationScale /= 2.0f;
                        if (m_options & c_UseXAML)
                        {
                            m_effectiveCompositionScaleX /= 2.0f;
                            m_effectiveCompositionScaleY /= 2.0f;
                        }
                    }
                }

                // �ʿ��� ������ ��� ũ�⸦ �ȼ� ������ ����մϴ�.
                m_outputSize.Width = m_logicalSize.Width * m_effectiveRasterizationScale;
                m_outputSize.Height = m_logicalSize.Height * m_effectiveRasterizationScale;

                // DirectX ������ ũ�⸦ 0���� ������ �ʽ��ϴ�.
                m_outputSize.Width = max(m_outputSize.Width, 1.0f);
                m_outputSize.Height = max(m_outputSize.Height, 1.0f);
            }
#endif
#pragma endregion

        }
    }    
}




