#pragma once
#include "DLLDefine.h"

namespace Engine
{
	namespace Type
	{
		//assimp에서 따왔다고 명시하기

		template <typename TReal>
		class ENGINE_API Vector2t {
		public:
			Vector2t() : x(), y() {}
			Vector2t(TReal _x, TReal _y) : x(_x), y(_y) {}
			explicit Vector2t(TReal _xyz) : x(_xyz), y(_xyz) {}
			Vector2t(const Vector2t& o) = default;

			void Set(TReal pX, TReal pY)
			{
				x = pX; y = pY;
			}
			Vector2t SquareLength() const
			{
				return x * x + y * y;
			}
			Vector2t Length() const
			{
				return std::sqrt(SquareLength());
			}
			Vector2t& Normalize()
			{
				*this /= Length();
				return *this;
			}

			const Vector2t& operator += (const Vector2t& o)
			{
				x += o.x; y += o.y;
				return *this;
			}
			const Vector2t& operator -= (const Vector2t& o)
			{
				x -= o.x; y -= o.y;
				return *this;
			}
			const Vector2t& operator *= (TReal f)
			{
				x *= f; y *= f;
				return *this;
			}
			const Vector2t& operator /= (TReal f)
			{
				x /= f; y /= f;
				return *this;
			}

			TReal operator[](unsigned int i) const
			{
				switch (i) {
				case 0:
					return x;
				case 1:
					return y;
				default:
					break;

				}
				return x;
			}

			bool operator== (const Vector2t& other) const
			{
				return x == other.x && y == other.y;
			}
			bool operator!= (const Vector2t& other) const
			{
				return x != other.x || y != other.y;
			}

			bool Equal(const Vector2t& other, TReal epsilon = std::numeric_limits<TReal>::epsilon()) const
			{
				return
					std::abs(x - other.x) <= epsilon &&
					std::abs(y - other.y) <= epsilon;
			}

			Vector2t& operator= (TReal f)
			{
				x = y = f;
				return *this;
			}
			const Vector2t SymMul(const Vector2t& o)
			{
				return Vector2t(x * o.x, y * o.y);
			}

			template <typename TOther>
			operator Vector2t<TOther>() const
			{
				return Vector2t<TOther>(static_cast<TOther>(x), static_cast<TOther>(y));
			}

			TReal x, y;
		};

		typedef Vector2t<float> Vector2f;
		typedef Vector2t<double> Vector2d;
		typedef Vector2t<int> Vector2i;

		// ------------------------------------------------------------------------------------------------
// symmetric addition
		template <typename TReal>
		inline
			Vector2t<TReal> operator + (const Vector2t<TReal>& v1, const Vector2t<TReal>& v2) {
			return Vector2t<TReal>(v1.x + v2.x, v1.y + v2.y);
		}

		// ------------------------------------------------------------------------------------------------
		// symmetric subtraction
		template <typename TReal>
		inline
			Vector2t<TReal> operator - (const Vector2t<TReal>& v1, const Vector2t<TReal>& v2) {
			return Vector2t<TReal>(v1.x - v2.x, v1.y - v2.y);
		}

		// ------------------------------------------------------------------------------------------------
		// scalar product
		template <typename TReal>
		inline
			TReal operator * (const Vector2t<TReal>& v1, const Vector2t<TReal>& v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}

		// ------------------------------------------------------------------------------------------------
		// scalar multiplication
		template <typename TReal>
		inline
			Vector2t<TReal> operator * (TReal f, const Vector2t<TReal>& v) {
			return Vector2t<TReal>(f * v.x, f * v.y);
		}

		// ------------------------------------------------------------------------------------------------
		// and the other way around
		template <typename TReal>
		inline
			Vector2t<TReal> operator * (const Vector2t<TReal>& v, TReal f) {
			return Vector2t<TReal>(f * v.x, f * v.y);
		}

		// ------------------------------------------------------------------------------------------------
		// scalar division
		template <typename TReal>
		inline
			Vector2t<TReal> operator / (const Vector2t<TReal>& v, TReal f) {
			return v * (1 / f);
		}

		// ------------------------------------------------------------------------------------------------
		// vector division
		template <typename TReal>
		inline
			Vector2t<TReal> operator / (const Vector2t<TReal>& v, const Vector2t<TReal>& v2) {
			return Vector2t<TReal>(v.x / v2.x, v.y / v2.y);
		}

		// ------------------------------------------------------------------------------------------------
		// vector negation
		template <typename TReal>
		inline
			Vector2t<TReal> operator - (const Vector2t<TReal>& v) {
			return Vector2t<TReal>(-v.x, -v.y);
		}

	}
}
