#pragma once

namespace SharedTypes
{
	template<typename TReal> class Matrix3x3t;
	template<typename TReal> class Matrix4x4t;

	// ---------------------------------------------------------------------------
/// @brief  Represents a three-dimensional vector.
// ---------------------------------------------------------------------------
	template <typename TReal>
	class Vector3t {
	public:
		/// @brief  The default class constructor.
		Vector3t() noexcept : x(), y(), z() {}

		/// @brief  The class constructor with the components.
		/// @param  _x  The x-component for the vector.
		/// @param  _y  The y-component for the vector.
		/// @param  _z  The z-component for the vector.
		Vector3t(TReal _x, TReal _y, TReal _z) : x(_x), y(_y), z(_z) {}

		/// @brief  The class constructor with a default value.
		/// @param  _xyz  The value for x, y and z.
		explicit Vector3t(TReal _xyz) : x(_xyz), y(_xyz), z(_xyz) {}

		/// @brief  The copy constructor.
		/// @param  o The instance to copy from.
		Vector3t(const Vector3t& o) = default;

		/// @brief  combined operators
		/// @brief  The copy constructor.
		const Vector3t& operator += (const Vector3t& o)
		{
			x += o.x;
			y += o.y;
			z += o.z;

			return *this;
		}

		/// @brief  The copy constructor.
		const Vector3t& operator -= (const Vector3t& o)
		{
			x -= o.x;
			y -= o.y;
			z -= o.z;

			return *this;
		}

		/// @brief  The copy constructor.
		const Vector3t& operator *= (TReal f)
		{
			x *= f;
			y *= f;
			z *= f;

			return *this;
		}

		/// @brief  The copy constructor.
		const Vector3t& operator /= (TReal f)
		{
			if (f == static_cast<TReal>(0.0)) {
				return *this;
			}
			const TReal invF = (TReal)1.0 / f;
			x *= invF;
			y *= invF;
			z *= invF;

			return *this;
		}

		/// @brief  Transform vector by matrix
		Vector3t& operator *= (const Matrix3x3t<TReal>& mat)
		{
			return (*this = mat * (*this));
		}

		Vector3t& operator *= (const Matrix4x4t<TReal>& mat)
		{
			return (*this = mat * (*this));
		}

		/// @brief  access a single element, const.
		TReal operator[](unsigned int i) const
		{
			switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				break;
			}
			return x;
		}

		/// @brief  access a single element, non-const.
		TReal& operator[](unsigned int i)
		{
			switch (i) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				break;
			}
			return x;
		}

		// comparison
		bool operator== (const Vector3t& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}
		bool operator!= (const Vector3t& other) const
		{
			return x != other.x || y != other.y || z != other.z;
		}
		bool operator < (const Vector3t& other) const
		{
			return x != other.x ? x < other.x : y != other.y ? y < other.y : z < other.z;
		}

		/// @brief  
		bool Equal(const Vector3t& other, TReal epsilon = std::numeric_limits<TReal>::epsilon()) const
		{
			return
				std::abs(x - other.x) <= epsilon &&
				std::abs(y - other.y) <= epsilon &&
				std::abs(z - other.z) <= epsilon;
		}

		template <typename TOther>
		operator Vector3t<TOther>() const
		{
			return Vector3t<TOther>(static_cast<TOther>(x), static_cast<TOther>(y), static_cast<TOther>(z));
		}

		/** @brief Set the components of a vector
		 *  @param pX X component
		 *  @param pY Y component
		 *  @param pZ Z component  */
		void Set(TReal pX, TReal pY, TReal pZ)
		{
			x = pX;
			y = pY;
			z = pZ;
		}

		/** @brief Get the squared length of the vector
		 *  @return Square length */
		TReal SquareLength() const
		{
			return x * x + y * y + z * z;
		}

		/** @brief Get the length of the vector
		 *  @return length */
		TReal Length() const
		{
			return std::sqrt(SquareLength());
		}

		/** @brief Normalize the vector */
		Vector3t& Normalize()
		{
			const TReal l = Length();
			if (l == 0) {
				return *this;
			}
			*this /= Length();

			return *this;
		}

		/** @brief Normalize the vector with extra check for zero vectors */
		Vector3t& NormalizeSafe()
		{
			TReal len = Length();
			if (len > static_cast<TReal>(0)) {
				*this /= len;
			}
			return *this;
		}

		/** @brief Componentwise multiplication of two vectors
		 *
		 *  Note that vec*vec yields the dot product.
		 *  @param o Second factor */
		const Vector3t SymMul(const Vector3t& o)
		{
			return Vector3t<TReal>(x * o.x, y * o.y, z * o.z);
		}

		TReal x, y, z;
	};

	typedef Vector3t<float> Vector3f;
	typedef Vector3t<double> Vector3d;
	typedef Vector3t<int> Vector3i;

	// ------------------------------------------------------------------------------------------------
/** Transformation of a vector by a 3x3 matrix */
	template <typename TReal>
	inline Vector3t<TReal> operator * (const Matrix3x3t<TReal>& pMatrix, const Matrix3x3t<TReal>& pVector) {
		Vector3t<TReal> res;
		res.x = pMatrix._11 * pVector.x + pMatrix._12 * pVector.y + pMatrix._13 * pVector.z;
		res.y = pMatrix._21 * pVector.x + pMatrix._22 * pVector.y + pMatrix._23 * pVector.z;
		res.z = pMatrix._31 * pVector.x + pMatrix._32 * pVector.y + pMatrix._33 * pVector.z;
		return res;
	}

	// ------------------------------------------------------------------------------------------------
	/** Transformation of a vector by a 4x4 matrix */
	template <typename TReal>
	inline Vector3t<TReal> operator * (const Matrix4x4t<TReal>& pMatrix, const Vector3t<TReal>& pVector) {
		Vector3t<TReal> res;
		res.x = pMatrix._11 * pVector.x + pMatrix._12 * pVector.y + pMatrix._13 * pVector.z + pMatrix._14;
		res.y = pMatrix._21 * pVector.x + pMatrix._22 * pVector.y + pMatrix._23 * pVector.z + pMatrix._24;
		res.z = pMatrix._31 * pVector.x + pMatrix._32 * pVector.y + pMatrix._33 * pVector.z + pMatrix._34;
		return res;
	}

	// ------------------------------------------------------------------------------------------------
	// symmetric addition
	template <typename TReal>
	inline Vector3t<TReal> operator + (const Vector3t<TReal>& v1, const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}
	// ------------------------------------------------------------------------------------------------
	// symmetric subtraction
	template <typename TReal>
	inline Vector3t<TReal> operator - (const Vector3t<TReal>& v1, const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}
	// ------------------------------------------------------------------------------------------------
	// scalar product
	template <typename TReal>
	inline TReal operator * (const Vector3t<TReal>& v1, const Vector3t<TReal>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	// ------------------------------------------------------------------------------------------------
	// scalar multiplication
	template <typename TReal>
	inline Vector3t<TReal> operator * (TReal f, const Vector3t<TReal>& v) {
		return Vector3t<TReal>(f * v.x, f * v.y, f * v.z);
	}
	// ------------------------------------------------------------------------------------------------
	// and the other way around
	template <typename TReal>
	inline Vector3t<TReal> operator * (const Vector3t<TReal>& v, TReal f) {
		return Vector3t<TReal>(f * v.x, f * v.y, f * v.z);
	}
	// ------------------------------------------------------------------------------------------------
	// scalar division
	template <typename TReal>
	inline Vector3t<TReal> operator / (const Vector3t<TReal>& v, TReal f) {
		return v * (1 / f);
	}
	// ------------------------------------------------------------------------------------------------
	// vector division
	template <typename TReal>
	inline Vector3t<TReal> operator / (const Vector3t<TReal>& v, const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v.x / v2.x, v.y / v2.y, v.z / v2.z);
	}
	// ------------------------------------------------------------------------------------------------
	// cross product
	template<typename TReal>
	inline Vector3t<TReal> operator ^ (const Vector3t<TReal>& v1, const Vector3t<TReal>& v2) {
		return Vector3t<TReal>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}
	// ------------------------------------------------------------------------------------------------
	// vector negation
	template<typename TReal>
	inline Vector3t<TReal> operator - (const Vector3t<TReal>& v) {
		return Vector3t<TReal>(-v.x, -v.y, -v.z);
	}
}


