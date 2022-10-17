#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Material
		{
		private:
			//texture�� Manager�� ������. ���� �⺻ ���ҽ��� ���� ������ ������.
			winrt::com_ptr<ID3D11ShaderResourceView> DiffuseMap;
			winrt::com_ptr<ID3D11ShaderResourceView> NormalMap;
			winrt::com_ptr<ID3D11ShaderResourceView> SpecularMap;
			//�̿��� ���� �ɼǵ�...
			void UpdateConstBuffers();
		public:
			void DrawMaterial();
			static const int DiffuseMapSlot = 0;
			static const int NormalMapSlot = 1;
			static const int SpecularMapSlot = 2;
		};

		class MaterialManager
		{
		public:
			//MaterialManager& GetInstance()
			//{
			//}
		private:
			MaterialManager();
			std::map<std::wstring, std::shared_ptr<Material>> Materials;			
		};
	}
}