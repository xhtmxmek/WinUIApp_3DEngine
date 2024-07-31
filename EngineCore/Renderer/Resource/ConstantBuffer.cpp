#include "pch.h"
#include "Renderer/Resource/DeviceResources.h"
#include "ConstantBuffer.h"
#include "RHIResource.h"
namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			ConstantBufferManager::ConstantBufferManager()
			{				
				CreateConstantBuffer(StaticConstBufferType::perObject, sizeof(ObjectConstBuffFormat));
				CreateConstantBuffer(StaticConstBufferType::perCamera, sizeof(CameraConstBuffFormat));
				CreateConstantBuffer(StaticConstBufferType::peRHIght, sizeof(LightBuffFormat));
				CreateConstantBuffer(StaticConstBufferType::perMaterial, sizeof(MaterialUniformBuffFormat));

			}

			void ConstantBufferManager::CreateConstantBuffer(StaticConstBufferType type, UINT size)

			{
				if (!ConstBuffer[(int)type])
				{
					auto device = DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
					CreateBufferFromData(&ConstBuffer[(int)type], D3D11_BIND_CONSTANT_BUFFER, nullptr,
						size, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
				}
			}

			void ConstantBufferManager::UpdateConstantBuffer(StaticConstBufferType type, void* rowData, UINT size)
			{
				D3D11_MAPPED_SUBRESOURCE mappedData;

				auto deviceContext = DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
				deviceContext->Map(ConstBuffer[(int)type].get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
				memcpy(mappedData.pData, rowData, size);
				deviceContext->Unmap(ConstBuffer[(int)type].get(), 0);

			}
			ID3D11Buffer** ConstantBufferManager::GetBuffer(StaticConstBufferType type)
			{
				return &ConstBuffer[(int)type];
			}
			void* ConstantBufferManager::LockUniformBuffer(StaticConstBufferType type)
			{
				D3D11_MAPPED_SUBRESOURCE mappedData;

				auto deviceContext = DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
				deviceContext->Map(ConstBuffer[(int)type].get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
				return mappedData.pData;
			}
			void ConstantBufferManager::UnLock(StaticConstBufferType type)
			{
				auto deviceContext = DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
				deviceContext->Unmap(ConstBuffer[(int)type].get(), 0);
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

			MaterialUniformBuffFormat* LockMaterialUniformBuffer()
			{
				ConstantBufferManager::GetInstance().LockUniformBuffer(StaticConstBufferType::perMaterial);
			}
			void UnLockMaterialUniformBuffer()
			{
				ConstantBufferManager::GetInstance().UnLock(StaticConstBufferType::perMaterial);
			}
		}
	}
}


