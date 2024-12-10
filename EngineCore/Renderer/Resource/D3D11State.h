#pragma once
#include "RHIresource.h"

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			class D3D11DepthStencilState : public RHIDepthStencilState
			{		
			public:			
				wil::com_ptr_nothrow<ID3D11DepthStencilState> _nativeResource;
			};

			D3D11_COMPARISON_FUNC GetD3D11Description(ComparisonFunc desc)
			{
				switch (desc)
				{
				case ComparisonFunc::Never:				
					return D3D11_COMPARISON_NEVER;				
				case ComparisonFunc::Less:
					return D3D11_COMPARISON_LESS;
				case ComparisonFunc::Equal:
					return D3D11_COMPARISON_EQUAL;
				case ComparisonFunc::LessEqual:
					return D3D11_COMPARISON_LESS_EQUAL;
				case ComparisonFunc::Greater:
					return D3D11_COMPARISON_GREATER;
				case ComparisonFunc::NotEqual:
					return D3D11_COMPARISON_NOT_EQUAL;
				case ComparisonFunc::GreaterEqual:
					return D3D11_COMPARISON_GREATER_EQUAL;
				default:
					return D3D11_COMPARISON_ALWAYS;
				}
			}

			D3D11_STENCIL_OP GetD3D11Description(StencilOperator desc)
			{
				switch (desc)
				{
					//Keep,
					//	Zero,
					//	Replace,
					//	SaturatedIncrement,
					//	SaturatedDecrement,
					//	Invert,
					//	Increment,
					//	Decrement,

					case StencilOperator::Zero:
						return D3D11_STENCIL_OP_ZERO;
					case StencilOperator::Replace:
						return D3D11_STENCIL_OP_REPLACE;
					case StencilOperator::SaturatedIncrement:
						return D3D11_STENCIL_OP_INCR_SAT;
					case StencilOperator::SaturatedDecrement:
						return D3D11_STENCIL_OP_DECR_SAT;
					case StencilOperator::Invert:
						return D3D11_STENCIL_OP_INVERT;
					case StencilOperator::Increment:
						return D3D11_STENCIL_OP_INCR;
					case StencilOperator::Decrement:
						return D3D11_STENCIL_OP_DECR;
					default:
						return D3D11_STENCIL_OP_KEEP;
				}
			}
		}
	}
}