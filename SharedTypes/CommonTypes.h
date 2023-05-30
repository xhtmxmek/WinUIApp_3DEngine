#pragma once

namespace SharedTypes
{
	struct Size
	{
		float Width;
		float Height;
		Size(const Size& src) :Width(src.Width), Height(src.Height) {}
		Size(float width, float height) :Width(width), Height(height) {}
		Size() :Width(0.0f), Height(0.0f) {}

		Size& operator=(const Size& src) { Width = src.Width; Height = src.Height; return *this; }

		bool operator==(const Size& src) { return ((Width == src.Width) && (Height == src.Height)); }
		bool operator!=(const Size& src) { return ((Width != src.Width) && (Height != src.Height)); }
	};		
}