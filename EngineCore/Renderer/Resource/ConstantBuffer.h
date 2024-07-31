#pragma once

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
				Vector4 IsSkinned;
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
			class ConstantBufferManager
			{
			private:
				wil::com_ptr_nothrow<ID3D11Buffer> ConstBuffer[(int)StaticConstBufferType::bufferType_max];
				std::unordered_map<string, wil::com_ptr_nothrow<ID3D11Buffer>> localBuffer;

				//DefaultShadingValueFormat ShadingValueFormat;
				ConstantBufferManager();

			public:
				void CreateConstantBuffer(StaticConstBufferType type, UINT size);
				void UpdateConstantBuffer(StaticConstBufferType type, void* rowData, UINT size);
				ID3D11Buffer** GetBuffer(StaticConstBufferType type);
				void* LockUniformBuffer(StaticConstBufferType type);
				void UnLock(StaticConstBufferType type);

				template<typename T>
				T* LockUniformBuffer(StaticConstBufferType type);


				static ConstantBufferManager& GetInstance();
				void Release();

			};

			MaterialUniformBuffFormat* LockMaterialUniformBuffer();
			void UnLockMaterialUniformBuffer();
		}
	}
}

