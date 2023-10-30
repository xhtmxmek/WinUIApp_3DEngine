#pragma once

namespace SharedTypes
{
	template <typename TReal>
	class Vector4t 
	{
	public:
		/// @brief  The default class constructor.
		Vector4t() noexcept : x(), y(), z(), w() {}

		/// @brief  The class constructor with the components.
		/// @param  _x  The x-component for the vector.
		/// @param  _y  The y-component for the vector.
		/// @param  _z  The z-component for the vector.
		Vector4t(TReal _x, TReal _y, TReal _z, TReal _w) : x(_x), y(_y), z(_z), w(_w) {}

		/// @brief  The class constructor with a default value.
		/// @param  _xyz  The value for x, y and z.
		explicit Vector4t(TReal _xyz) : x(_xyz), y(_xyz), z(_xyz), w(_xyz) {}

		/// @brief  The copy constructor.
		/// @param  o The instance to copy from.
		Vector4t(const Vector4t& o) = default;

		TReal x, y, z, w;
	};

	typedef Vector4t<float> Vector4f;
	typedef Vector4t<double> Vector4d;
	typedef Vector4t<int> Vector4i;
}