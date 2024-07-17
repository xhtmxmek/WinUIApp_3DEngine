#pragma once

namespace Engine
{
	namespace Renderer
	{
		class PrimitiveInfo
		{
		public:
			PrimitiveInfo() = default;
		};

		class StaticPrimitiveInfo : public PrimitiveInfo
		{
		public:
			StaticPrimitiveInfo() = default;

		};

		class DynamicPrimitiveInfo : public PrimitiveInfo
		{
		public:
			DynamicPrimitiveInfo() = default;
		};
	}
}