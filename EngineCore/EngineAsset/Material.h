#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Material
		{
		private:
			//texture�� Manager�� ������. ���� �⺻ ���ҽ��� ���� ������ ������.
			wil::com_ptr<ID3D11ShaderResourceView> DiffuseMap;
			wil::com_ptr<ID3D11ShaderResourceView> NormalMap;
			wil::com_ptr<ID3D11ShaderResourceView> SpecularMap;
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
			std::map<const wchar_t*, std::shared_ptr<Material>> Materials;			
		};
	}
}