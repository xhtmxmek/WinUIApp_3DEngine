#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RLI
		{
			class Buffer
			{				
				//virtual void 
			};

			class VertexInput
			{
				Buffer vertexbuffer;
				/*
				* VertexDeclation
				* -InputVertexElements(D3D11_Input_Element_Desc의 Array)
				* -geometry buffer를 위한 stream?steram?
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