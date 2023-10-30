#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace GraphicsLibrary
		{
			class ConstantBufferManager
			{
			public:
				enum class StaticConstBufferType
				{
					perObject,
					perCamera,
					perLight,
					bufferType_max,
				};

			public:
				struct ObjectConstBuffFormat
				{
					Matrix4x4f World;
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

				//struct DefaultShadingValueFormat
				//{
				//	float Diffuse;
				//	float Specular;
				//	float Ambient;
				//	float Padding;	//버리는 값
				//	Vector4f HeightMapInfo;
				//};

				struct LightBuffFormat
				{
					Vector4f LightPos[100];
					Vector4f LightDir[100];
					Vector4f LightColor[100];
					Vector4i LightCount;

				};

			private:
				wil::com_ptr_nothrow<ID3D11Buffer> ConstBuffer[(int)StaticConstBufferType::bufferType_max];
				std::unordered_map<string, wil::com_ptr_nothrow<ID3D11Buffer>> localBuffer;

				//DefaultShadingValueFormat ShadingValueFormat;
				ConstantBufferManager();

			public:
				void CreateConstantBuffer(StaticConstBufferType type, UINT size);
				void UpdateConstantBuffer(StaticConstBufferType type, void* rowData, UINT size);
				ID3D11Buffer** GetBuffer(StaticConstBufferType type);

				static ConstantBufferManager& GetInstance();
				void Release();

			};
		}
	}
}

