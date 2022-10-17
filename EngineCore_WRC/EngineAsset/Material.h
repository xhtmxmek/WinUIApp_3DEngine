#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Material
		{
		private:
			//texture는 Manager가 관리함. 엔진 기본 리소스는 엔진 시작지 생성됨.
			winrt::com_ptr<ID3D11ShaderResourceView> DiffuseMap;
			winrt::com_ptr<ID3D11ShaderResourceView> NormalMap;
			winrt::com_ptr<ID3D11ShaderResourceView> SpecularMap;
			//이외의 각종 옵션들...
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