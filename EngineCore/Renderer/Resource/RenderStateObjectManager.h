#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace GraphicsLibrary
		{
			enum class RasterizerCullMode
			{
				None = 1,
				Front = 2,
				Back = 3,
			};

			enum class RasterizerFillMode
			{
				WireFrame = 2,
				Solid = 3,
			};

			enum class textureAdressMode
			{
				Wrap = 1,
				Mirror = 2,
				Clamp = 3,
			};

			enum class SamplerFilter
			{
				Point,
				Linear,
				Anisotrophic
			};

			enum class ComparisonFunc
			{
				Never = 1,
				Less = 2,
				Equal = 3,
				LessEqual = 4,
				Greater = 5,
				NotEqual = 6,
				Equal = 7,
				Always = 8
			};

			enum class BlendOperator
			{
				Add,
				Subtract,
				RevSubtract,
				Min,
				Max
			};

			enum class BlendFactor
			{
				Zero = 1,
				One,
				SourceColor,
				InverseSourceColor,
				SourceAlpha,
				InverseSourceAlpha,
				DestAlpha,
				InverseDestAlpha,
				DestColor,
				InverseDestColor,
				BlendFactor,
				//BF_InverseConstantBlendFactor,
				//BF_Source1Color,
				//BF_InverseSource1Color,
				//BF_Source1Alpha,
				//BF_InverseSource1Alpha,
			};

			struct RasterizerState
			{
				wil::com_ptr_nothrow<ID3D11RasterizerState> nativeState_;
			};

			struct SamplerState
			{
				wil::com_ptr_nothrow<ID3D11SamplerState> nativeState_;
			};

			struct DepthStencilState
			{
				//impl로 뺴는건 나중에..귀찮다
				wil::com_ptr_nothrow<ID3D11DepthStencilState> nativeState_;
			};

			struct BlendState
			{
				wil::com_ptr_nothrow<ID3D11BlendState> nativeState_;
			};

			static RasterizerState DefaultRasterizerState;
			static SamplerState DefaultSamplerState;
			static BlendState DefaultBlendState;
			static DepthStencilState DefaultDepthStencilState;


			class RenderStateObjectManger
			{
			public:
				enum class RasterizingType
				{
					Default,		//solid, cull_backface,
					Default_CullFront,
					Default_CullNone,
					Wire,	//cull_backface,
					WireCullFront,
					WireCullNone,
					MaxRasterzingType,
				};

				enum class SamplerType
				{
					Default,
					Anisotropic,
					Clamp,
					MaxSamplerType,
				};

				enum class BlendingType
				{
					Default,	//none
					AlphaBlend,
					MaxBlendingType,
				};

				enum class DepthStencilType
				{
					Default,
					NoWrite,
					MaxDepthStencilType
				};

			private:
				//ID3D11SamplerState* SamplerState[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];	
				//ID3D11RasterizerState* RasterizerStates[(int)RasterizingType::MaxRasterzingType];
				//ID3D11DepthStencilState* DepthStencilStates[(int)DepthStencilType::MaxDepthStencilType];
				//ID3D11BlendState* BlendStates[(int)BlendingType::MaxBlendingType];

				static RasterizerState rasterizerState_;
				static SamplerState samplerState_;
				static DepthStencilState depthState_;
				static BlendState blendState_;
			public:
				static RenderStateObjectManger& const GetInstance();
				void Init();

				static RasterizerState GetRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull);
				static SamplerState GetSamplerState(textureAdressMode textureAdress, SamplerFilter filter);
				static BlendState GetBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor);
				static DepthStencilState GetDepthStencilState(ComparisonFunc DepthTest, bool depthWrite);
				//ID3D11SamplerState* const* const GetSamplerStates();
				//ID3D11BlendState* const GetBlendState(RenderStateObjectManger::BlendingType type);
				//ID3D11RasterizerState* const GetRasterizerSate(RenderStateObjectManger::RasterizingType type);
				//ID3D11DepthStencilState* const GetDepthStencilState(RenderStateObjectManger::DepthStencilType type);
				void Release();
			private:
				//여러 셰이더객체.cpp에서 접근에서 사용해야 하기에 싱글톤으로!
				RenderStateObjectManger();

				static void InitRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull, RasterizerState& outState);
				static void InitSamplerState(textureAdressMode textureAdress, SamplerFilter filter, SamplerState& outState);
				static void InitDepthStencilState(ComparisonFunc DepthTest, bool depthWrite, DepthStencilState& outState);
				static void InitBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor, BlendState& outState);
			};
		}
	}
}