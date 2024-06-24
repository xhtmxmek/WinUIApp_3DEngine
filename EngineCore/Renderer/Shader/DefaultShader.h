#pragma once
#include "ShaderObject.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RLI
		{
			class DefaultShader : public ShaderObject
			{
			private:
				void SetDefault();
				//Property<float> Diffuse;
				//Property<float> Specular;
				//Property<float> Ambient;

			public:
				DefaultShader();
				~DefaultShader();

				//virtual void CreateConstantBuffer() override;
				virtual bool CompileShader() override;
				virtual void UpdateConstantBuffer(void* constBuffPtr);
				virtual void SetShaderOnPipeline() override;

			private:

			};
		}
	}
}
