#pragma once

#include "RenderResources.h"
#include "RHIUtilities.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			class RHIDepthStencilState;

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
				GreaterEqual = 7,
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

			enum class StencilOperator
			{
				Keep,
				Zero,
				Replace,
				SaturatedIncrement,
				SaturatedDecrement,
				Invert,
				Increment,
				Decrement,
			};


			template<typename StateType, typename RHIStatePrivate, typename RHIRenderStatePtr>
			class StaticState
			{
			public:
				static RHIRenderStatePtr GetRHI()
				{
					return StaticResource._rhiState;
				}
			private:
				class StaticStateResource : public RenderResource
				{
				public:
					RHIStatePrivate _rhiState;

					StaticStateResource()
					{						
						InitResource();
					}

					virtual void CreateRHI()
					{
						_rhiState = StateType::CreateRHI();
					}
					virtual void ReleaseRHI()
					{
						_rhiState.ReleaseRHI();
					}
				};

				static StaticStateResource StaticResource;
			};

			template<typename StateType, typename RHIStatePrivate, typename RHIRenderStatePtr>
			typename StaticState<StateType, RHIStatePrivate, RHIRenderStatePtr>::StaticStateResource StaticState<StateType, RHIStatePrivate, RHIRenderStatePtr>::StaticResource = StaticState<StateType, RHIStatePrivate, RHIRenderStatePtr>::StaticStateResource();

			struct DepthStencilDesc
			{
				bool enableDepthWrite;
				ComparisonFunc depthTest;
				bool enableFrontFaceStencil;
				ComparisonFunc frontFaceStencilTest;
				StencilOperator frontFaceFailStencilOp;
				StencilOperator frontFaceDepthFailStencilOp;
				StencilOperator frontFacePassStencilOp;
				bool enableBackFaceStencil;
				ComparisonFunc backFaceStencilTest;
				StencilOperator backFaceFailStencilOp;
				StencilOperator backFaceDepthFailStencilOp;
				StencilOperator backFacePassStencilOp;
				unsigned char stencilReadMask = 0xFF;
				unsigned char stencilWriteMask = 0xFF;

				DepthStencilDesc(bool inEnableDepthWrite = true,
					ComparisonFunc inDepthTest = ComparisonFunc::LessEqual,
					bool inEnableFrontFaceStencil = false,
					ComparisonFunc inFrontFaceStencilTest = ComparisonFunc::Always,
					StencilOperator inFrontFaceStenilFailStencilOp = StencilOperator::Keep,
					StencilOperator inFrontFaceDepthFailStencilOp = StencilOperator::Keep,
					StencilOperator inFrontFacePassStencilOp = StencilOperator::Keep,
					bool inEnableBackFaceStencil = false,
					ComparisonFunc inBackFaceStencilTest = ComparisonFunc::Always,
					StencilOperator inBackFaceStenilFailStencilOp = StencilOperator::Keep,
					StencilOperator inBackFaceDepthFailStencilOp = StencilOperator::Keep,
					StencilOperator inBackFacePassStencilOp = StencilOperator::Keep,
					unsigned char inStencilReadMask = 0xFF,
					unsigned char inStencilWriteMask = 0xFF)
					:enableDepthWrite(inEnableDepthWrite),
					depthTest(inDepthTest),
					enableFrontFaceStencil(inEnableFrontFaceStencil),
					frontFaceStencilTest(inFrontFaceStencilTest),
					frontFaceFailStencilOp(inFrontFaceStenilFailStencilOp),
					frontFaceDepthFailStencilOp(inFrontFaceDepthFailStencilOp),
					frontFacePassStencilOp(inFrontFacePassStencilOp),
					enableBackFaceStencil(inEnableBackFaceStencil),
					backFaceStencilTest(inBackFaceStencilTest),
					backFaceFailStencilOp(inBackFaceDepthFailStencilOp),
					backFaceDepthFailStencilOp(inBackFaceDepthFailStencilOp),
					backFacePassStencilOp(inBackFacePassStencilOp),
					stencilReadMask(inStencilReadMask),
					stencilWriteMask(inStencilWriteMask)
				{
				}
			};

			template<bool enableDepthWrite = true,
				ComparisonFunc depthTest = ComparisonFunc::LessEqual,
				bool enableFrontFaceStencil = false,
				ComparisonFunc frontFaceStencilTest = ComparisonFunc::Always,
				StencilOperator frontFaceStenilFailStencilOp = StencilOperator::Keep,
				StencilOperator frontFaceDepthFailStencilOp = StencilOperator::Keep,
				StencilOperator frontFacePassStencilOp = StencilOperator::Keep,
				bool enableBackFaceStencil = false,
				ComparisonFunc backFaceStencilTest = ComparisonFunc::Always,
				StencilOperator backFaceStenilFailStencilOp = StencilOperator::Keep,
				StencilOperator backFaceDepthFailStencilOp = StencilOperator::Keep,
				StencilOperator backFacePassStencilOp = StencilOperator::Keep,
				unsigned char stencilReadMask = 0xFF,
				unsigned char stencilWriteMask = 0xFF>
			class DepthStencilState : public StaticState<
				DepthStencilState<
				enableDepthWrite,
				depthTest,
				enableFrontFaceStencil,
				frontFaceStencilTest,
				frontFaceStenilFailStencilOp,
				frontFaceDepthFailStencilOp,
				enableBackFaceStencil,
				backFaceStencilTest,
				backFaceStenilFailStencilOp,
				backFaceDepthFailStencilOp,
				backFacePassStencilOp,
				stencilReadMask,
				stencilWriteMask
				>,
				shared_ptr<RHIDepthStencilState>,
				weak_ptr<RHIDepthStencilState>>
			{
			public:
				static weak_ptr<RHIDepthStencilState>& CreateRHI()
				{
					DepthStencilDesc depthDesc(enableDepthWrite,
						depthTest,
						enableFrontFaceStencil,
						frontFaceStencilTest,
						frontFaceStenilFailStencilOp,
						frontFaceDepthFailStencilOp,
						frontFacePassStencilOp,
						enableBackFaceStencil,
						backFaceStencilTest,
						backFaceStenilFailStencilOp,
						backFaceDepthFailStencilOp,
						backFacePassStencilOp,
						stencilReadMask,
						stencilWriteMask
					);

					//Called When Rhi resources initiailize. there is only one static state at same template.
					return RHI::CreateRHIDepthStencilState();
				}
			};
		}


		//struct RasterizerState
		//{
		//	wil::com_ptr_nothrow<ID3D11RasterizerState> nativeState_;
		//};

		//class RenderStateObjectManger
		//{
		//public:
		//	enum class RasterizingType
		//	{
		//		Default,		//solid, cull_backface,
		//		Default_CullFront,
		//		Default_CullNone,
		//		Wire,	//cull_backface,
		//		WireCullFront,
		//		WireCullNone,
		//		MaxRasterzingType,
		//	};

		//	enum class SamplerType
		//	{
		//		Default,
		//		Anisotropic,
		//		Clamp,
		//		MaxSamplerType,
		//	};

		//	enum class BlendingType
		//	{
		//		Default,	//none
		//		AlphaBlend,
		//		MaxBlendingType,
		//	};

		//	enum class DepthStencilType
		//	{
		//		Default,
		//		NoWrite,
		//		MaxDepthStencilType
		//	};

		//private:
		//	//ID3D11SamplerState* SamplerState[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];	
		//	//ID3D11RasterizerState* RasterizerStates[(int)RasterizingType::MaxRasterzingType];
		//	//ID3D11DepthStencilState* DepthStencilStates[(int)DepthStencilType::MaxDepthStencilType];
		//	//ID3D11BlendState* BlendStates[(int)BlendingType::MaxBlendingType];


		/*MeshProcessor settings are determined according to material options or pass. Pattern it into a function according to meshPass or material pass and register it in the table using each pass as a key.
		*Afterwards, refer to the key when creating a meshProcessor in each pass.
		*Register the corresponding object in the PSO table when creating a render state during the mesh draw command creation process.
		When submitting a draw command, if the psoID of the command exists in the table, write it.
		*/

		// 
		//	
		//	*/
		//	//
		//public:
		//	static RenderStateObjectManger& const GetInstance()
		//	{

		//	}
		//	void Init();

		//	static RasterizerState GetRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull);
		//	static SamplerState GetSamplerState(textureAdressMode textureAdress, SamplerFilter filter);
		//	static BlendState GetBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor);
		//	static DepthStencilState GetDepthStencilState(ComparisonFunc DepthTest, bool depthWrite);
		//	//ID3D11SamplerState* const* const GetSamplerStates();
		//	//ID3D11BlendState* const GetBlendState(RenderStateObjectManger::BlendingType type);
		//	//ID3D11RasterizerState* const GetRasterizerSate(RenderStateObjectManger::RasterizingType type);
		//	//ID3D11DepthStencilState* const GetDepthStencilState(RenderStateObjectManger::DepthStencilType type);
		//	void Release();
		//private:
		//	RenderStateObjectManger();

		//	static void InitRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull, RasterizerState& outState);
		//	static void InitSamplerState(textureAdressMode textureAdress, SamplerFilter filter, SamplerState& outState);
		//	static void InitDepthStencilState(ComparisonFunc DepthTest, bool depthWrite, DepthStencilState& outState);
		//	static void InitBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor, BlendState& outState);
		//};		
	}
}