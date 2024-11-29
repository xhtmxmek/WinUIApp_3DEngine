#pragma once

#include "RenderResources.h"
#include "RHIUtilities.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			enum class StaticConstBufferType
			{
				perObject,
				perCamera,
				peRHIght,
				perMaterial,
				bufferType_max,
			};

			struct ObjectConstBuffFormat
			{
				Matrix4x4f World;
				Matrix4x4f WorldViewProj;
				Matrix4x4f InverseWorld;
				Vector4f IsSkinned;
				Matrix4x4f SkinMatrix[6];
				Matrix4x4f NormalMatrix[6];
				Vector4i TessellationFactor;
			};

			struct CameraConstBuffFormat
			{
				Matrix4x4f View;
				Matrix4x4f Proj;
				Vector4f CamPos;
				Vector4f CamDir;
				Vector4f minMaxDistance;
				Vector4f minMaxLOD;
			};

			struct MaterialUniformBuffFormat
			{
				Color4f DiffuseColor;
				Color4f AmbientColor;
				Color4f SpecularColor;
				Vector4f HeightMapInfo;
			};

			struct LightBuffFormat
			{
				Vector4f LightPos[100];
				Vector4f LightDir[100];
				Vector4f LightColor[100];
				Vector4i LightCount;

			};


			/*Static ConstantBuffer는 템플릿으로 쪼갤 이유가 생각나는게 없다.
			* depthstencilState는 desc에 따라서 State가 나뉜다. 같은 파라메터 목록을 가지고 있지만 인자값에 따라서 새로운 객체가 생성.
			* 상수버퍼는 구조체 멤버 자체에 따라서 버퍼를 새로 만드는것. 심지어 내용은 동적으로 업데이트 가능.
			* Static Resource로 만들어야 되는것은 맞음. 하나의 버퍼를 바인딩해놓고 필요할때 교체하는것이 여러개의 버퍼를 갈아끼는 것보다 저렴함.
			*/

			template<typename BufferType, typename RHIBufferPrivate, typename RHIBufferPtr>
			class StaticConstantBuffer
			{
			public:
				static RHIBufferPtr GetRHI()
				{
					return StaticResource._rhiBuffer;
				}

				void UpdateConstantBuffer(BufferType* src)
				{
					StaticResource._rhiBuffer->Update(src); //안쪽에서 mapping.
										
					//RHI::UpdateConstantBuffer()
				}
			private:
				class StaticConstantBuffer : public RenderResource
				{
				public:
					RHIBufferPrivate _rhiBuffer;

					StaticConstantBuffer()
					{
						InitResource();
					}

					virtual void CreateRHI()
					{
						_rhiBuffer = RHIBufferPtr::CreateRHI();
					}
					virtual void ReleaseRHI()
					{
						_rhiBuffer.ReleaseRHI();
					}
					
					BufferType* LockBuffer();
					void UnLockBuffer();
				};

				static StaticConstantBuffer StaticResource;
			};






			//class ConstantBufferManager
			//{
			//private:
			//	wil::com_ptr_nothrow<ID3D11Buffer> ConstBuffer[(int)StaticConstBufferType::bufferType_max];
			//	std::unordered_map<string, wil::com_ptr_nothrow<ID3D11Buffer>> localBuffer;

			//	//DefaultShadingValueFormat ShadingValueFormat;
			//	ConstantBufferManager() = default;
			//	void CreateConstantBuffer(StaticConstBufferType type, UINT size);
			//public:
			//	void Init();				
			//	void UpdateConstantBuffer(StaticConstBufferType type, void* rowData, UINT size);
			//	ID3D11Buffer** GetBuffer(StaticConstBufferType type);
			//	void* LockUniformBuffer(StaticConstBufferType type);
			//	void UnLock(StaticConstBufferType type);

			//	template<typename T>
			//	T* LockUniformBuffer(StaticConstBufferType type);


			//	static ConstantBufferManager& GetInstance();
			//	void Release();

			//};

			//MaterialUniformBuffFormat* LockMaterialUniformBuffer();
			//void UnLockMaterialUniformBuffer();
		}
	}
}

