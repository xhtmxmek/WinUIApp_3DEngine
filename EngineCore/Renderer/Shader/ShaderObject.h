#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RLI
		{
			class ShaderObject
			{

			protected:
				wil::com_ptr<ID3D11VertexShader> VertexShader;
				wil::com_ptr<ID3D11PixelShader> PixelShader;
				wil::com_ptr<ID3D11HullShader> HullShader;
				wil::com_ptr<ID3D11DomainShader> DomainShader;
				wil::com_ptr<ID3D11ComputeShader> ComputeShader;
				wil::com_ptr<ID3D11InputLayout> VertexLayout;

			public:
				ShaderObject() {}
				ShaderObject(const ShaderObject&) = delete;

				virtual bool CompileShader() = 0;	//이름으로 Shader를 받아서 컴파일 하는 부분은 같음. CompileShader로 바꿔야겠당
				//void Release();

				virtual void SetShaderOnPipeline() = 0;
				//virtual void CreateConstantBuffer() = 0;
			};
		}
	}
}
