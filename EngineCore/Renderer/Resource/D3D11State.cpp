#include "pch.h"
#include "RenderResources.h"
#include "DX11Context.h"
#include "RendererBaseHeader.h"
#include "D3D11State.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			shared_ptr<RHIDepthStencilState> DX11Context::CreateRHIDepthStencilState(const DepthStencilDesc& desc)
			{
				D3D11_DEPTH_STENCIL_DESC d3d11Desc;
				d3d11Desc.DepthEnable = desc.depthTest != ComparisonFunc::Always || desc.enableDepthWrite;
				d3d11Desc.DepthWriteMask = desc.enableDepthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;

				d3d11Desc.StencilEnable = desc.enableBackFaceStencil || desc.enableFrontFaceStencil;
				d3d11Desc.StencilReadMask = desc.stencilReadMask;
				d3d11Desc.StencilWriteMask = desc.stencilWriteMask;

				d3d11Desc.FrontFace.StencilFunc = GetD3D11Description(desc.frontFaceStencilTest);
				d3d11Desc.FrontFace.StencilPassOp = GetD3D11Description(desc.frontFacePassStencilOp);
				d3d11Desc.FrontFace.StencilFailOp = GetD3D11Description(desc.frontFaceFailStencilOp);
				d3d11Desc.FrontFace.StencilDepthFailOp = GetD3D11Description(desc.frontFaceDepthFailStencilOp);

				d3d11Desc.BackFace.StencilFunc = GetD3D11Description(desc.backFaceStencilTest);
				d3d11Desc.BackFace.StencilPassOp = GetD3D11Description(desc.backFacePassStencilOp);
				d3d11Desc.BackFace.StencilFailOp = GetD3D11Description(desc.backFaceFailStencilOp);
				d3d11Desc.BackFace.StencilDepthFailOp = GetD3D11Description(desc.backFaceDepthFailStencilOp);

				shared_ptr<D3D11DepthStencilState> depthstencilState = make_shared<D3D11DepthStencilState>();				
				_d3dDevice->CreateDepthStencilState(&d3d11Desc, depthstencilState->_nativeResource.put());
				return depthstencilState;
			}
		}
	}
}