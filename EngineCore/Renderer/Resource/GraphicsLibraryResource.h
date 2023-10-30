#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace GraphicsLibrary
		{
			HRESULT CreateBufferFromData(ID3D11Buffer** ppBuffer, D3D11_BIND_FLAG eBindFlag,
				void* pData, UINT nDataSize, D3D11_USAGE eUsage, UINT CPUAccessFlags);
		}
	}
}