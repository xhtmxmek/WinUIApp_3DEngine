#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		enum class ShaderType
		{
			Vertex = 0,
			Hull,
			Domain,
			Geometry,
			Pixel,
			Compute,
		};


		class Shader
		{
		public:
			Shader();
			virtual bool Load(const wstring& name, ShaderType type) = 0;			
		private:			
			wstring name_;
			wil::com_ptr<ID3D11ShaderReflection> reflection_;
			ShaderType shaderType;
		};

		class VertexShader
		{
		public:
			VertexShader();	
			virtual bool Load(const wstring& name, ShaderType type);
		private:			
			wil::com_ptr<ID3D11VertexShader> shaderObject_;			
		};

		class PixelShader
		{
		public:
			PixelShader();
			bool Load(const wstring& name, ShaderType type);
		private:
			wil::com_ptr<ID3D11VertexShader> shaderObject_;
		};
	}
}