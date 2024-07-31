#pragma once
#include "RenderResource.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
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
				Always = 7
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

			template<typename StateType, typename RHIRenderState>
			class StaticState
			{
			public:
				static RHIRenderState GetRHI()
				{
					return StaticResource._rhiState;
				}
			private:
				class StaticStateResource : public RenderResource
				{					
				public:
					RHIRenderState _rhiState;

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

			struct DepthStencilDesc
			{
				bool enableDepthWrite;
				ComparisonFunc depthTest;
				bool enableFrontFaceStencil;
				ComparisonFunc frontFaceStencilTest;
				StencilOperator frontFaceStenilFailStencilOp;
				StencilOperator frontFaceDepthFailStencilOp;
				StencilOperator frontFacePassStencilOp;
				bool enableBackFaceStencil;
				ComparisonFunc backFaceStencilTest;
				StencilOperator backFaceStenilFailStencilOp;
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
					frontFaceStenilFailStencilOp(inFrontFaceStenilFailStencilOp),
					frontFaceDepthFailStencilOp(inFrontFaceDepthFailStencilOp),
					frontFacePassStencilOp(inFrontFacePassStencilOp),
					enableBackFaceStencil(inEnableBackFaceStencil),
					backFaceStencilTest(inBackFaceStencilTest),
					backFaceStenilFailStencilOp(inBackFaceDepthFailStencilOp),
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
			RHIDepthStencilState
			{
			public:
				static shared_ptr<DepthStencilStateRHI>& CreateRHI() override
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

					//RHI 리소스가 초기화 될때 호출됨. 같은 템플릿에 대해 static State는 하나임.
					return RHI::CreateRHIDepthStencilState();
				}
			};

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
			//	//basePass�� RenderState
			//	//������ pass�� RenderState

			//	/*
			//	* 머티리얼 옵션이나 pass에 따른 MeshPropassor 세팅은 정해져있음. meshPass나 material pass에 따라서 함수로 패턴화 해놓고
			//	* 각 pass를 key로 삼아서 테이블에 등록해놓기.
			//	* 이후 각 pass에서 meshProcessor를 만들때는 해당 키를 참조한다.
			//	* 메시 드로우 커맨드 생성 과정에서 렌더스테이트 만들때 pso테이블에 해당 객체 등록하기.
			//	* 드로우 커맨드 서밋할때 테이블에서 커맨드의 psoID가 테이블에 존재하면 가져다 쓰기. 아니면
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
			//	//���� ���̴���ü.cpp���� ���ٿ��� ����ؾ� �ϱ⿡ �̱�������!
			//	RenderStateObjectManger();

			//	static void InitRasterizerState(RasterizerFillMode fillMode, RasterizerCullMode cull, RasterizerState& outState);
			//	static void InitSamplerState(textureAdressMode textureAdress, SamplerFilter filter, SamplerState& outState);
			//	static void InitDepthStencilState(ComparisonFunc DepthTest, bool depthWrite, DepthStencilState& outState);
			//	static void InitBlendState(bool blendEnable, BlendFactor srcFactor, BlendFactor destFactor, BlendState& outState);
			};
		}
	}
}