#pragma once

namespace Engine
{
	namespace Type
	{
		struct Size
		{
			float Width;
			float Height;
			Size(const Size& src) :Width(src.Width), Height(src.Height) {}
			Size(float width, float height) :Width(width), Height(height) {}
			Size() :Width(0.0f), Height(0.0f) {}
		};
	}
}