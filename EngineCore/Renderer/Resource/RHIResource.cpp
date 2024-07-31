#include "pch.h"
#include "Renderer/Resource/DeviceResources.h"
#include <Windows.h>
#include "RHIResource.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{			
			HRESULT CreateBufferFromData(ID3D11Buffer** ppBuffer, D3D11_BIND_FLAG eBindFlag,
				void* pData, UINT nDataSize, D3D11_USAGE eUsage, UINT CPUAccessFlags)
			{
				ID3D11Device* device = DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();

				//�Ŀ� ������	����, �߰�/ �Һ� ���� Ȥ�� ����Ʈ ���۸� ����ϰ� �Ǹ� miscflag�� structsize�� �����ϵ��� �����. 
				D3D11_BUFFER_DESC bd = { nDataSize  , eUsage , (UINT)eBindFlag , CPUAccessFlags , 0 , 0 }; //2d,3d�ؽ��İ� �ƴϸ� pitch������ �ǹ� ����
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