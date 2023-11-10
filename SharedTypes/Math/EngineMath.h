#pragma once

namespace SharedTypes
{
	constexpr float MATH_PI = 3.141592654f;
	constexpr float MATH_2PI = 6.283185307f;
	constexpr float MATH_PIDIV2 = 1.570796327f;
	constexpr float MATH_PIDIV4 = 0.785398163f;

	constexpr float ConvertToRadian(float fDegrees) noexcept { return fDegrees * (MATH_PI / 180.0f); }
	constexpr float ConvertToDegrees(float fRadians) noexcept { return fRadians * (180.0f / MATH_PI); }
}