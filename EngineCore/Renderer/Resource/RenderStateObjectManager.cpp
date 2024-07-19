#include "pch.h"
#include "RenderStateObjectManager.h"
#include "DeviceResources.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RLI
		{
			RenderStateObjectManger::RenderStateObjectManger()
			{
			}

			void RenderStateObjectManger::InitRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull, RasterizerState& outState)
			{
				D3D11_RASTERIZER_DESC rasterizerDesc;
				rasterizerDesc.FillMode = static_cast<D3D11_FILL_MODE>(fillMode);
				rasterizerDesc.CullMode = static_cast<D3D11_CULL_MODE>(cull);
				rasterizerDesc.FrontCounterClockwise = FALSE;
				rasterizerDesc.DepthBias = 0;		//�׸���  �� ��� �ٽ� �����ϱ�
				rasterizerDesc.SlopeScaledDepthBias = 0.0f;
				rasterizerDesc.DepthBiasClamp = 0.0f;
				rasterizerDesc.ScissorEnable = false;
				rasterizerDesc.DepthClipEnable = true;
				rasterizerDesc.AntialiasedLineEnable = false;

				auto d3dDevice = DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
				d3dDevice->CreateRasterizerState(&rasterizerDesc, outState.nativeState_.put());
			}

			void RenderStateObjectManger::InitSamplerState(textureAdressMode textureAdress, SamplerFilter filter, SamplerState& outState)
			{
				D3D11_SAMPLER_DESC samplerDesc;
				samplerDesc.Filter = static_cast<D3D11_FILTER>(filter);
				D3D11_TEXTURE_ADDRESS_MODE d3d11TexMode = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(textureAdress);
				samplerDesc.AddressU = d3d11TexMode;
				samplerDesc.AddressV = d3d11TexMode;
				samplerDesc.AddressW = d3d11TexMode;
				samplerDesc.MipLODBias = 0;
				samplerDesc.MaxAnisotropy = 1;
				samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				for (int i = 0; i < 4; i++)
					samplerDesc.BorderColor[i] = 0;
				samplerDesc.MinLOD = 0;
				samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;			//<---- no upperLimit

				auto device = DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
				device->CreateSamplerState(&samplerDesc, outState.nativeState_.put());
			}

			void RenderStateObjectManger::InitDepthStencilState(ComparisonFunc DepthTest, bool depthWrite, DepthStencilState& outState)
			{
				D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
				depthStencilDesc.DepthEnable = true;
				if (depthWrite == true)
					depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				else
					depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

				depthStencilDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(DepthTest);
				depthStencilDesc.StencilEnable = false;
				depthStencilDesc.StencilReadMask = 0xFF;
				depthStencilDesc.StencilWriteMask = 0xFF;

				depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				auto d3dDevice = DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
				d3dDevice->CreateDepthStencilState(&depthStencilDesc, outState.nativeState_.put());
			}

			void RenderStateObjectManger::InitBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor, BlendState& outState)
			{
				D3D11_BLEND_DESC blendDesc;

				//alphablend state
				blendDesc.AlphaToCoverageEnable = false;
				blendDesc.IndependentBlendEnable = false;
				blendDesc.RenderTarget[0].BlendEnable = blendEnable;
				blendDesc.RenderTarget[0].SrcBlend = static_cast<D3D11_BLEND>(srcFactor);
				blendDesc.RenderTarget[0].DestBlend = static_cast<D3D11_BLEND>(destFactor);
				blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
				blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
				auto device = DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
				device->CreateBlendState(&blendDesc, outState.nativeState_.put());
			}

			void RenderStateObjectManger::Init()
			{
				InitRasterizerState(RasterizerFillMode::Solid, RasterizerCullMode::Back, DefaultRasterizerState);
				InitSamplerState(textureAdressMode::Wrap, SamplerFilter::Linear, DefaultSamplerState);
				InitDepthStencilState(ComparisonFunc::LessEqual, true, DefaultDepthStencilState);
				InitBlendState(false, BlendFactor::One, BlendFactor::Zero, DefaultBlendState);
			}

			void RenderStateObjectManger::Release()
			{
				rasterizerState_.nativeState_->Release();
				samplerState_.nativeState_->Release();
				depthState_.nativeState_->Release();
				blendState_.nativeState_->Release();
			}

			RasterizerState RenderStateObjectManger::GetRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull)
			{
				InitRasterizerState(fillMode, cull, rasterizerState_);
				return rasterizerState_;
			}

			SamplerState RenderStateObjectManger::GetSamplerState(textureAdressMode textureAdress, SamplerFilter filter)
			{
				InitSamplerState(textureAdress, filter, samplerState_);
				return samplerState_;
			}

			BlendState RenderStateObjectManger::GetBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor)
			{
				InitBlendState(blendEnable, srcFactor, destFactor, blendState_);
				return blendState_;
			}

			DepthStencilState RenderStateObjectManger::GetDepthStencilState(ComparisonFunc DepthTest, bool depthWrite)
			{
				InitDepthStencilState(DepthTest, depthWrite, depthState_);
				return depthState_;
			}
}
	}
}