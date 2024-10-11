#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{						
			enum class SceneColorFormat
			{
				b8r8g8a8_unorm,
				d24_s8_uint,
			};
			
			//enum class min

			class RHIResource
			{
				virtual void CreateRHI() = 0;
				virtual void ReleaseRHI() = 0;
				//virtual void GetRHI();
			};

			class RHIDepthStencilState : public RHIResource
			{
			};


			class Buffer
			{				
				//virtual void 
			};

			class VertexInput
			{
				Buffer vertexbuffer;
				/*
				* VertexDeclation
				* -InputVertexElements(D3D11_Input_Element_Desc Array)
				* -for geometry buffer stream?steram?
				*/								
				//layoutPointer?
			};

			class DX11Buffer : public Buffer
			{
				wil::com_ptr<ID3D11Buffer> rawBuffer;
			};

			HRESULT CreateBufferFromData(ID3D11Buffer** ppBuffer, D3D11_BIND_FLAG eBindFlag,
				void* pData, UINT nDataSize, D3D11_USAGE eUsage, UINT CPUAccessFlags);
		}
	}
}