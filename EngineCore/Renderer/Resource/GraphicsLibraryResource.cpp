#include "pch.h"
#include "GraphicsLibraryResource.h"
#include "Renderer/Resource/DeviceResources.h"

namespace Engine
{
	namespace Renderer
	{
		namespace GraphicsLibrary
		{
			HRESULT CreateBufferFromData(ID3D11Buffer** ppBuffer, D3D11_BIND_FLAG eBindFlag,
				void* pData, UINT nDataSize, D3D11_USAGE eUsage, UINT CPUAccessFlags)
			{
				ID3D11Device* device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();

				//후에 구조적	버퍼, 추가/ 소비 버퍼 혹은 바이트 버퍼를 사용하게 되면 miscflag와 structsize도 지정하도록 만들기. 
				D3D11_BUFFER_DESC bd = { nDataSize  , eUsage , (UINT)eBindFlag , CPUAccessFlags , 0 , 0 }; //2d,3d텍스쳐가 아니면 pitch값들은 의미 없음
				D3D11_SUBRESOURCE_DATA subResourceData = { pData , 0 ,0 };
				HRESULT hr = S_OK;
				D3D11_SUBRESOURCE_DATA* pSubResourceData = nullptr;

				if (pData)
					pSubResourceData = &subResourceData;

				if (device)
					hr = device->CreateBuffer(&bd, pSubResourceData, ppBuffer);
				return hr;
			}
		}
	}
}