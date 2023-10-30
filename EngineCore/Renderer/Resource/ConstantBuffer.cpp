#include "pch.h"
#include "Renderer/Resource/DeviceResources.h"
#include "ConstantBuffer.h"
#include "GraphicsLibraryResource.h"
namespace Engine
{
	namespace Renderer
	{
		namespace GraphicsLibrary
		{
			ConstantBufferManager::ConstantBufferManager()
			{
			}

			void ConstantBufferManager::CreateConstantBuffer(StaticConstBufferType type, UINT size)

			{
				if (!ConstBuffer[(int)type])
				{
					auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
					CreateBufferFromData(&ConstBuffer[(int)type], D3D11_BIND_CONSTANT_BUFFER, nullptr,
						size, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
				}
			}

			void ConstantBufferManager::UpdateConstantBuffer(StaticConstBufferType type, void* rowData, UINT size)
			{
				D3D11_MAPPED_SUBRESOURCE mappedData;

				auto deviceContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
				deviceContext->Map(ConstBuffer[(int)type].get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
				memcpy(mappedData.pData, rowData, size);
				deviceContext->Unmap(ConstBuffer[(int)type].get(), 0);

			}
			ID3D11Buffer** ConstantBufferManager::GetBuffer(StaticConstBufferType type)
			{
				return &ConstBuffer[(int)type];
			}
			ConstantBufferManager& ConstantBufferManager::GetInstance()
			{
				static ConstantBufferManager instance;
				return instance;
			}

			void ConstantBufferManager::Release()
			{
				for (int i = 0; i < (int)StaticConstBufferType::bufferType_max; i++)
					ConstBuffer[(int)i].reset();
			}
		}
	}
}


