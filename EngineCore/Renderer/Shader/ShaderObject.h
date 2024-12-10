#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
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

				virtual bool CompileShader() = 0;	//�̸����� Shader�� �޾Ƽ� ������ �ϴ� �κ��� ����. CompileShader�� �ٲ�߰ڴ�
				//void Release();

				virtual void SetShaderOnPipeline() = 0;
				//virtual void CreateConstantBuffer() = 0;
			};
		}
	}
}
