﻿/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2022, assimp team



All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/
/** @file matrix4x4.h
 *  @brief 4x4 matrix structure, including operators when compiling in C++
 */

#pragma once
#include "DllDefine.h"

namespace Engine
{
	namespace Type
	{
		template<typename TReal> class Matrix3x3t;
		template<typename TReal> class Quaterniont;

		// ---------------------------------------------------------------------------
		/** @brief Represents a row-major 4x4 matrix, use this for homogeneous
		 *   coordinates.
		 *
		 *  There's much confusion about matrix layouts (column vs. row order).
		 *  This is *always* a row-major matrix. Not even with the
		 *  #aiProcess_ConvertToLeftHanded flag, which absolutely does not affect
		 *  matrix order - it just affects the handedness of the coordinate system
		 *  defined thereby.
		 */
		template<typename TReal>
		class Matrix4x4t {
		public:
			/** set to identity */
			Matrix4x4t() noexcept
				:
				_11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f),
				_21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f),
				_31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f),
				_41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
			{}
			// empty


			/** construction from single values */
			Matrix4x4t(TReal m00, TReal m01, TReal m02, TReal m03,
				TReal m10, TReal m11, TReal m12, TReal m13,
				TReal m20, TReal m21, TReal m22, TReal m23,
				TReal m30, TReal m31, TReal m32, TReal m33)
				:
				_11(m00), _12(m01), _13(m02), _14(m03),
				_21(m10), _22(m11), _23(m12), _24(m13),
				_31(m20), _32(m21), _33(m22), _34(m23),
				_41(m30), _42(m31), _43(m32), _44(m33) 
			{ // empty
			}


				/** construction from 3x3 matrix, remaining elements are set to identity */
			explicit Matrix4x4t(const Matrix3x3t<TReal>& m)
			{
				_11 = m._11; _12 = m._12; _13 = m._13; _14 = static_cast<TReal>(0.0);
				_21 = m._21; _22 = m._22; _23 = m._23; _24 = static_cast<TReal>(0.0);
				_31 = m._31; _32 = m._32; _33 = m._33; _34 = static_cast<TReal>(0.0);
				_41 = static_cast<TReal>(0.0); _42 = static_cast<TReal>(0.0); _43 = static_cast<TReal>(0.0); _44 = static_cast<TReal>(1.0);
			}

				/** construction from position, rotation and scaling components
				 * @param scaling The scaling for the x,y,z axes
				 * @param rotation The rotation as a hamilton quaternion
				 * @param position The position for the x,y,z axes
				 */
			Matrix4x4t(const Vector3t<TReal>& scaling, const Quaterniont<TReal>& rotation,
				const Vector3t<TReal>& position)
			{
				// build a 3x3 rotation matrix
				aiMatrix3x3t<TReal> m = rotation.GetMatrix();

				_11 = m._11 * scaling.x;
				_12 = m._12 * scaling.x;
				_13 = m._13 * scaling.x;
				_14 = position.x;

				_21 = m._21 * scaling.y;
				_22 = m._22 * scaling.y;
				_23 = m._23 * scaling.y;
				_24 = position.y;

				_31 = m._31 * scaling.z;
				_32 = m._32 * scaling.z;
				_33 = m._33 * scaling.z;
				_34 = position.z;

				_41 = static_cast<TReal>(0.0);
				_42 = static_cast<TReal>(0.0);
				_43 = static_cast<TReal>(0.0);
				_44 = static_cast<TReal>(1.0);
				}

				// array access operators
				/** @fn TReal* operator[] (unsigned int p_iIndex)
				 *  @param [in] p_iIndex - index of the row.
				 *  @return pointer to pointed row.
				 */
				TReal* operator[]       (unsigned int p_iIndex);

				/** @fn const TReal* operator[] (unsigned int p_iIndex) const
				 *  @overload TReal* operator[] (unsigned int p_iIndex)
				 */
				const TReal* operator[] (unsigned int p_iIndex) const;

				// comparison operators
				bool operator== (const Matrix4x4t & m) const;
				bool operator!= (const Matrix4x4t & m) const;

				bool Equal(const Matrix4x4t & m, TReal epsilon = ai_epsilon) const;

				// matrix multiplication.
				Matrix4x4t& operator *= (const Matrix4x4t& m)
				{
					*this = aiMatrix4x4t<TReal>(
						m._11 * _11 + m._21 * _12 + m._31 * _13 + m._41 * _14,
						m._12 * _11 + m._22 * _12 + m._32 * _13 + m._42 * _14,
						m._13 * _11 + m._23 * _12 + m._33 * _13 + m._43 * _14,
						m._14 * _11 + m._24 * _12 + m._34 * _13 + m._44 * _14,
						m._11 * _21 + m._21 * _22 + m._31 * _23 + m._41 * _24,
						m._12 * _21 + m._22 * _22 + m._32 * _23 + m._42 * _24,
						m._13 * _21 + m._23 * _22 + m._33 * _23 + m._43 * _24,
						m._14 * _21 + m._24 * _22 + m._34 * _23 + m._44 * _24,
						m._11 * _31 + m._21 * _32 + m._31 * _33 + m._41 * _34,
						m._12 * _31 + m._22 * _32 + m._32 * _33 + m._42 * _34,
						m._13 * _31 + m._23 * _32 + m._33 * _33 + m._43 * _34,
						m._14 * _31 + m._24 * _32 + m._34 * _33 + m._44 * _34,
						m._11 * _41 + m._21 * _42 + m._31 * _43 + m._41 * _44,
						m._12 * _41 + m._22 * _42 + m._32 * _43 + m._42 * _44,
						m._13 * _41 + m._23 * _42 + m._33 * _43 + m._43 * _44,
						m._14 * _41 + m._24 * _42 + m._34 * _43 + m._44 * _44);
					return *this;
				}
				Matrix4x4t  operator *  (const Matrix4x4t& m) const
				{
					aiMatrix4x4t<TReal> temp(*this);
					temp *= m;
					return temp;
				}

				Matrix4x4t operator * (const TReal& aFloat) const
				{
					aiMatrix4x4t<TReal> temp(
						_11 * aFloat,
						_12 * aFloat,
						_13 * aFloat,
						_14 * aFloat,
						_21 * aFloat,
						_22 * aFloat,
						_23 * aFloat,
						_24 * aFloat,
						_31 * aFloat,
						_32 * aFloat,
						_33 * aFloat,
						_34 * aFloat,
						_41 * aFloat,
						_42 * aFloat,
						_43 * aFloat,
						_44 * aFloat);
					return temp;
				}
				Matrix4x4t operator + (const Matrix4x4t& aMatrix) const
				{
					aiMatrix4x4t<TReal> temp(
						m._11 + _11,
						m._12 + _12,
						m._13 + _13,
						m._14 + _14,
						m._21 + _21,
						m._22 + _22,
						m._23 + _23,
						m._24 + _24,
						m._31 + _31,
						m._32 + _32,
						m._33 + _33,
						m._34 + _34,
						m._41 + _41,
						m._42 + _42,
						m._43 + _43,
						m._44 + _44);
					return temp;
				}

				template <typename TOther>
				operator Matrix4x4t<TOther>() const;

				// -------------------------------------------------------------------
				/** @brief Transpose the matrix */
				Matrix4x4t& Transpose();

				// -------------------------------------------------------------------
				/** @brief Invert the matrix.
				 *  If the matrix is not invertible all elements are set to qnan.
				 *  Beware, use (f != f) to check whether a TReal f is qnan.
				 */
				Matrix4x4t& Inverse();
				TReal Determinant() const;


				// -------------------------------------------------------------------
				/** @brief Returns true of the matrix is the identity matrix.
				 *  The check is performed against a not so small epsilon.
				 */
				inline bool IsIdentity() const;

				// -------------------------------------------------------------------
				/** @brief Decompose a trafo matrix into its original components
				 *  @param scaling Receives the output scaling for the x,y,z axes
				 *  @param rotation Receives the output rotation as a hamilton
				 *   quaternion
				 *  @param position Receives the output position for the x,y,z axes
				 */
				void Decompose(Vector3t<TReal>&scaling, Quaterniont<TReal>&rotation,
					Vector3t<TReal>&position) const;

				// -------------------------------------------------------------------
				/** @fn void Decompose(Vector3t<TReal>& pScaling, Vector3t<TReal>& pRotation, Vector3t<TReal>& pPosition) const
				 *  @brief Decompose a trafo matrix into its original components.
				 * Thx to good FAQ at http://www.gamedev.ru/code/articles/faq_matrix_quat
				 *  @param [out] pScaling - Receives the output scaling for the x,y,z axes.
				 *  @param [out] pRotation - Receives the output rotation as a Euler angles.
				 *  @param [out] pPosition - Receives the output position for the x,y,z axes.
				 */
				void Decompose(Vector3t<TReal>&pScaling, Vector3t<TReal>&pRotation, Vector3t<TReal>&pPosition) const;

				// -------------------------------------------------------------------
				/** @fn void Decompose(Vector3t<TReal>& pScaling, Vector3t<TReal>& pRotationAxis, TReal& pRotationAngle, Vector3t<TReal>& pPosition) const
				 *  @brief Decompose a trafo matrix into its original components
				 * Thx to good FAQ at http://www.gamedev.ru/code/articles/faq_matrix_quat
				 *  @param [out] pScaling - Receives the output scaling for the x,y,z axes.
				 *  @param [out] pRotationAxis - Receives the output rotation axis.
				 *  @param [out] pRotationAngle - Receives the output rotation angle for @ref pRotationAxis.
				 *  @param [out] pPosition - Receives the output position for the x,y,z axes.
				 */
				void Decompose(Vector3t<TReal>&pScaling, Vector3t<TReal>&pRotationAxis, TReal & pRotationAngle, Vector3t<TReal>&pPosition) const;

				// -------------------------------------------------------------------
				/** @brief Decompose a trafo matrix with no scaling into its
				 *    original components
				 *  @param rotation Receives the output rotation as a hamilton
				 *    quaternion
				 *  @param position Receives the output position for the x,y,z axes
				 */
				void DecomposeNoScaling(Quaterniont<TReal>&rotation,
					Vector3t<TReal>&position) const;

				// -------------------------------------------------------------------
				/** @brief Creates a trafo matrix from a set of euler angles
				 *  @param x Rotation angle for the x-axis, in radians
				 *  @param y Rotation angle for the y-axis, in radians
				 *  @param z Rotation angle for the z-axis, in radians
				 */
				Matrix4x4t& FromEulerAnglesXYZ(TReal x, TReal y, TReal z);
				Matrix4x4t& FromEulerAnglesXYZ(const Vector3t<TReal>&blubb);

				// -------------------------------------------------------------------
				/** @brief Returns a rotation matrix for a rotation around the x axis
				 *  @param a Rotation angle, in radians
				 *  @param out Receives the output matrix
				 *  @return Reference to the output matrix
				 */
				static Matrix4x4t& RotationX(TReal a, Matrix4x4t & out);

				// -------------------------------------------------------------------
				/** @brief Returns a rotation matrix for a rotation around the y axis
				 *  @param a Rotation angle, in radians
				 *  @param out Receives the output matrix
				 *  @return Reference to the output matrix
				 */
				static Matrix4x4t& RotationY(TReal a, Matrix4x4t & out);

				// -------------------------------------------------------------------
				/** @brief Returns a rotation matrix for a rotation around the z axis
				 *  @param a Rotation angle, in radians
				 *  @param out Receives the output matrix
				 *  @return Reference to the output matrix
				 */
				static Matrix4x4t& RotationZ(TReal a, Matrix4x4t & out);

				// -------------------------------------------------------------------
				/** Returns a rotation matrix for a rotation around an arbitrary axis.
				 *  @param a Rotation angle, in radians
				 *  @param axis Rotation axis, should be a normalized vector.
				 *  @param out Receives the output matrix
				 *  @return Reference to the output matrix
				 */
				static Matrix4x4t& Rotation(TReal a, const Vector3t<TReal>&axis,
					Matrix4x4t & out);

				// -------------------------------------------------------------------
				/** @brief Returns a translation matrix
				 *  @param v Translation vector
				 *  @param out Receives the output matrix
				 *  @return Reference to the output matrix
				 */
				static Matrix4x4t& Translation(const Vector3t<TReal>&v,
					Matrix4x4t & out);

				// -------------------------------------------------------------------
				/** @brief Returns a scaling matrix
				 *  @param v Scaling vector
				 *  @param out Receives the output matrix
				 *  @return Reference to the output matrix
				 */
				static Matrix4x4t& Scaling(const Vector3t<TReal>&v, Matrix4x4t & out);

				// -------------------------------------------------------------------
				/** @brief A function for creating a rotation matrix that rotates a
				 *  vector called "from" into another vector called "to".
				 * Input : from[3], to[3] which both must be *normalized* non-zero vectors
				 * Output: mtx[3][3] -- a 3x3 matrix in column-major form
				 * Authors: Tomas Mueller, John Hughes
				 *          "Efficiently Building a Matrix to Rotate One Vector to Another"
				 *          Journal of Graphics Tools, 4(4):1-4, 1999
				 */
				static Matrix4x4t& FromToMatrix(const Vector3t<TReal>&from,
					const Vector3t<TReal>&to, Matrix4x4t & out);

				TReal _11, _12, _13, _14;
				TReal _21, _22, _23, _24;
				TReal _31, _32, _33, _34;
				TReal _41, _42, _43, _44;
			};

			typedef Matrix4x4t<float> Matrix4x4f;
			typedef Matrix4x4t<double> Matrix4x4d;

			// ------------------------------------------------------------------------------------------------
			template <typename TReal>
			template <typename TOther>
			aiMatrix4x4t<TReal>::operator aiMatrix4x4t<TOther>() const {
				return aiMatrix4x4t<TOther>(static_cast<TOther>(_11), static_cast<TOther>(_12), static_cast<TOther>(_13), static_cast<TOther>(_14),
					static_cast<TOther>(_21), static_cast<TOther>(_22), static_cast<TOther>(_23), static_cast<TOther>(_24),
					static_cast<TOther>(_31), static_cast<TOther>(_32), static_cast<TOther>(_33), static_cast<TOther>(_34),
					static_cast<TOther>(_41), static_cast<TOther>(_42), static_cast<TOther>(_43), static_cast<TOther>(_44));
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Transpose() {
				// (TReal&) don't remove, GCC complains cause of packed fields
				std::swap((TReal&)_21, (TReal&)_12);
				std::swap((TReal&)_31, (TReal&)_13);
				std::swap((TReal&)_32, (TReal&)_23);
				std::swap((TReal&)_41, (TReal&)_14);
				std::swap((TReal&)_42, (TReal&)_24);
				std::swap((TReal&)_43, (TReal&)_34);
				return *this;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				TReal aiMatrix4x4t<TReal>::Determinant() const {
				return _11 * _22 * _33 * _44 - _11 * _22 * _34 * _43 + _11 * _23 * _34 * _42 - _11 * _23 * _32 * _44
					+ _11 * _24 * _32 * _43 - _11 * _24 * _33 * _42 - _12 * _23 * _34 * _41 + _12 * _23 * _31 * _44
					- _12 * _24 * _31 * _43 + _12 * _24 * _33 * _41 - _12 * _21 * _33 * _44 + _12 * _21 * _34 * _43
					+ _13 * _24 * _31 * _42 - _13 * _24 * _32 * _41 + _13 * _21 * _32 * _44 - _13 * _21 * _34 * _42
					+ _13 * _22 * _34 * _41 - _13 * _22 * _31 * _44 - _14 * _21 * _32 * _43 + _14 * _21 * _33 * _42
					- _14 * _22 * _33 * _41 + _14 * _22 * _31 * _43 - _14 * _23 * _31 * _42 + _14 * _23 * _32 * _41;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Inverse() {
				// Compute the reciprocal determinant
				const TReal det = Determinant();
				if (det == static_cast<TReal>(0.0))
				{
					// Matrix not invertible. Setting all elements to nan is not really
					// correct in a mathematical sense but it is easy to debug for the
					// programmer.
					const TReal nan = std::numeric_limits<TReal>::quiet_NaN();
					*this = aiMatrix4x4t<TReal>(
						nan, nan, nan, nan,
						nan, nan, nan, nan,
						nan, nan, nan, nan,
						nan, nan, nan, nan);

					return *this;
				}

				const TReal invdet = static_cast<TReal>(1.0) / det;

				aiMatrix4x4t<TReal> res;
				res._11 = invdet * (_22 * (_33 * _44 - _34 * _43) + _23 * (_34 * _42 - _32 * _44) + _24 * (_32 * _43 - _33 * _42));
				res._12 = -invdet * (_12 * (_33 * _44 - _34 * _43) + _13 * (_34 * _42 - _32 * _44) + _14 * (_32 * _43 - _33 * _42));
				res._13 = invdet * (_12 * (_23 * _44 - _24 * _43) + _13 * (_24 * _42 - _22 * _44) + _14 * (_22 * _43 - _23 * _42));
				res._14 = -invdet * (_12 * (_23 * _34 - _24 * _33) + _13 * (_24 * _32 - _22 * _34) + _14 * (_22 * _33 - _23 * _32));
				res._21 = -invdet * (_21 * (_33 * _44 - _34 * _43) + _23 * (_34 * _41 - _31 * _44) + _24 * (_31 * _43 - _33 * _41));
				res._22 = invdet * (_11 * (_33 * _44 - _34 * _43) + _13 * (_34 * _41 - _31 * _44) + _14 * (_31 * _43 - _33 * _41));
				res._23 = -invdet * (_11 * (_23 * _44 - _24 * _43) + _13 * (_24 * _41 - _21 * _44) + _14 * (_21 * _43 - _23 * _41));
				res._24 = invdet * (_11 * (_23 * _34 - _24 * _33) + _13 * (_24 * _31 - _21 * _34) + _14 * (_21 * _33 - _23 * _31));
				res._31 = invdet * (_21 * (_32 * _44 - _34 * _42) + _22 * (_34 * _41 - _31 * _44) + _24 * (_31 * _42 - _32 * _41));
				res._32 = -invdet * (_11 * (_32 * _44 - _34 * _42) + _12 * (_34 * _41 - _31 * _44) + _14 * (_31 * _42 - _32 * _41));
				res._33 = invdet * (_11 * (_22 * _44 - _24 * _42) + _12 * (_24 * _41 - _21 * _44) + _14 * (_21 * _42 - _22 * _41));
				res._34 = -invdet * (_11 * (_22 * _34 - _24 * _32) + _12 * (_24 * _31 - _21 * _34) + _14 * (_21 * _32 - _22 * _31));
				res._41 = -invdet * (_21 * (_32 * _43 - _33 * _42) + _22 * (_33 * _41 - _31 * _43) + _23 * (_31 * _42 - _32 * _41));
				res._42 = invdet * (_11 * (_32 * _43 - _33 * _42) + _12 * (_33 * _41 - _31 * _43) + _13 * (_31 * _42 - _32 * _41));
				res._43 = -invdet * (_11 * (_22 * _43 - _23 * _42) + _12 * (_23 * _41 - _21 * _43) + _13 * (_21 * _42 - _22 * _41));
				res._44 = invdet * (_11 * (_22 * _33 - _23 * _32) + _12 * (_23 * _31 - _21 * _33) + _13 * (_21 * _32 - _22 * _31));
				*this = res;

				return *this;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				TReal* aiMatrix4x4t<TReal>::operator[](unsigned int p_iIndex) {
				if (p_iIndex > 3) {
					return nullptr;
				}
				switch (p_iIndex) {
				case 0:
					return &_11;
				case 1:
					return &_21;
				case 2:
					return &_31;
				case 3:
					return &_41;
				default:
					break;
				}
				return &_11;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				const TReal* aiMatrix4x4t<TReal>::operator[](unsigned int p_iIndex) const {
				if (p_iIndex > 3) {
					return nullptr;
				}

				switch (p_iIndex) {
				case 0:
					return &_11;
				case 1:
					return &_21;
				case 2:
					return &_31;
				case 3:
					return &_41;
				default:
					break;
				}
				return &_11;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				bool aiMatrix4x4t<TReal>::operator== (const aiMatrix4x4t<TReal>& m) const {
				return (_11 == m._11 && _12 == m._12 && _13 == m._13 && _14 == m._14 &&
					_21 == m._21 && _22 == m._22 && _23 == m._23 && _24 == m._24 &&
					_31 == m._31 && _32 == m._32 && _33 == m._33 && _34 == m._34 &&
					_41 == m._41 && _42 == m._42 && _43 == m._43 && _44 == m._44);
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				bool aiMatrix4x4t<TReal>::operator!= (const aiMatrix4x4t<TReal>& m) const {
				return !(*this == m);
			}

			// ---------------------------------------------------------------------------
			template<typename TReal>
			AI_FORCE_INLINE
				bool aiMatrix4x4t<TReal>::Equal(const aiMatrix4x4t<TReal>& m, TReal epsilon) const {
				return
					std::abs(_11 - m._11) <= epsilon &&
					std::abs(_12 - m._12) <= epsilon &&
					std::abs(_13 - m._13) <= epsilon &&
					std::abs(_14 - m._14) <= epsilon &&
					std::abs(_21 - m._21) <= epsilon &&
					std::abs(_22 - m._22) <= epsilon &&
					std::abs(_23 - m._23) <= epsilon &&
					std::abs(_24 - m._24) <= epsilon &&
					std::abs(_31 - m._31) <= epsilon &&
					std::abs(_32 - m._32) <= epsilon &&
					std::abs(_33 - m._33) <= epsilon &&
					std::abs(_34 - m._34) <= epsilon &&
					std::abs(_41 - m._41) <= epsilon &&
					std::abs(_42 - m._42) <= epsilon &&
					std::abs(_43 - m._43) <= epsilon &&
					std::abs(_44 - m._44) <= epsilon;
			}

			// ----------------------------------------------------------------------------------------

#define ASSIMP_MATRIX4_4_DECOMPOSE_PART		\
	const aiMatrix4x4t<TReal>& _this = *this;/* Create alias for conveniance. */ \
	\
	/* extract translation */ \
	pPosition.x = _this[0][3]; \
	pPosition.y = _this[1][3]; \
	pPosition.z = _this[2][3]; \
	\
	/* extract the columns of the matrix. */ \
	aiVector3t<TReal> vCols[3] = { \
		aiVector3t<TReal>(_this[0][0],_this[1][0],_this[2][0]), \
		aiVector3t<TReal>(_this[0][1],_this[1][1],_this[2][1]), \
		aiVector3t<TReal>(_this[0][2],_this[1][2],_this[2][2]) \
	}; \
	\
	/* extract the scaling factors */ \
	pScaling.x = vCols[0].Length(); \
	pScaling.y = vCols[1].Length(); \
	pScaling.z = vCols[2].Length(); \
	\
	/* and the sign of the scaling */ \
	if (Determinant() < 0) pScaling = -pScaling; \
	\
	/* and remove all scaling from the matrix */ \
	if(pScaling.x) vCols[0] /= pScaling.x; \
	if(pScaling.y) vCols[1] /= pScaling.y; \
	if(pScaling.z) vCols[2] /= pScaling.z; \
	\
	do {} while(false)

			template <typename TReal>
			AI_FORCE_INLINE
				void aiMatrix4x4t<TReal>::Decompose(aiVector3t<TReal>& pScaling, aiQuaterniont<TReal>& pRotation,
					aiVector3t<TReal>& pPosition) const {
				ASSIMP_MATRIX4_4_DECOMPOSE_PART;

				// build a 3x3 rotation matrix
				aiMatrix3x3t<TReal> m(vCols[0].x, vCols[1].x, vCols[2].x,
					vCols[0].y, vCols[1].y, vCols[2].y,
					vCols[0].z, vCols[1].z, vCols[2].z);

				// and generate the rotation quaternion from it
				pRotation = aiQuaterniont<TReal>(m);
			}

			template <typename TReal>
			AI_FORCE_INLINE
				void aiMatrix4x4t<TReal>::Decompose(aiVector3t<TReal>& pScaling, aiVector3t<TReal>& pRotation, aiVector3t<TReal>& pPosition) const {
				ASSIMP_MATRIX4_4_DECOMPOSE_PART;

				/*
				assuming a right-handed coordinate system
				and post-multiplication of column vectors,
				the rotation matrix for an euler XYZ rotation is M = Rz * Ry * Rx.
				combining gives:

					|  CE  BDE-AF  ADE+BF  0  |
				M = |  CF  BDF+AE  ADF-BE  0  |
					|  -D    CB      AC    0  |
					|   0     0       0    1  |

				where
				A = cos(angle_x), B = sin(angle_x);
				C = cos(angle_y), D = sin(angle_y);
				E = cos(angle_z), F = sin(angle_z);
				*/

				// Use a small epsilon to solve floating-point inaccuracies
				const TReal epsilon = Assimp::Math::getEpsilon<TReal>();

				pRotation.y = std::asin(-vCols[0].z);// D. Angle around oY.

				TReal C = std::cos(pRotation.y);

				if (std::fabs(C) > epsilon)
				{
					// Finding angle around oX.
					TReal tan_x = vCols[2].z / C;// A
					TReal tan_y = vCols[1].z / C;// B

					pRotation.x = std::atan2(tan_y, tan_x);
					// Finding angle around oZ.
					tan_x = vCols[0].x / C;// E
					tan_y = vCols[0].y / C;// F
					pRotation.z = std::atan2(tan_y, tan_x);
				}
				else
				{// oY is fixed.
					pRotation.x = 0;// Set angle around oX to 0. => A == 1, B == 0, C == 0, D == 1.

					// And finding angle around oZ.
					TReal tan_x = vCols[1].y;// BDF+AE => E
					TReal tan_y = -vCols[1].x;// BDE-AF => F

					pRotation.z = std::atan2(tan_y, tan_x);
				}
			}

#undef ASSIMP_MATRIX4_4_DECOMPOSE_PART

			template <typename TReal>
			AI_FORCE_INLINE
				void aiMatrix4x4t<TReal>::Decompose(aiVector3t<TReal>& pScaling, aiVector3t<TReal>& pRotationAxis, TReal& pRotationAngle,
					aiVector3t<TReal>& pPosition) const {
				aiQuaterniont<TReal> pRotation;

				Decompose(pScaling, pRotation, pPosition);
				pRotation.Normalize();

				TReal angle_cos = pRotation.w;
				TReal angle_sin = std::sqrt(1.0f - angle_cos * angle_cos);

				pRotationAngle = std::acos(angle_cos) * 2;

				// Use a small epsilon to solve floating-point inaccuracies
				const TReal epsilon = 10e-3f;

				if (std::fabs(angle_sin) < epsilon) angle_sin = 1;

				pRotationAxis.x = pRotation.x / angle_sin;
				pRotationAxis.y = pRotation.y / angle_sin;
				pRotationAxis.z = pRotation.z / angle_sin;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				void aiMatrix4x4t<TReal>::DecomposeNoScaling(aiQuaterniont<TReal>& rotation,
					aiVector3t<TReal>& position) const {
				const aiMatrix4x4t<TReal>& _this = *this;

				// extract translation
				position.x = _this[0][3];
				position.y = _this[1][3];
				position.z = _this[2][3];

				// extract rotation
				rotation = aiQuaterniont<TReal>((aiMatrix3x3t<TReal>)_this);
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::FromEulerAnglesXYZ(const aiVector3t<TReal>& blubb) {
				return FromEulerAnglesXYZ(blubb.x, blubb.y, blubb.z);
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::FromEulerAnglesXYZ(TReal x, TReal y, TReal z) {
				aiMatrix4x4t<TReal>& _this = *this;

				TReal cx = std::cos(x);
				TReal sx = std::sin(x);
				TReal cy = std::cos(y);
				TReal sy = std::sin(y);
				TReal cz = std::cos(z);
				TReal sz = std::sin(z);

				// mz*my*mx
				_this._11 = cz * cy;
				_this._12 = cz * sy * sx - sz * cx;
				_this._13 = sz * sx + cz * sy * cx;

				_this._21 = sz * cy;
				_this._22 = cz * cx + sz * sy * sx;
				_this._23 = sz * sy * cx - cz * sx;

				_this._31 = -sy;
				_this._32 = cy * sx;
				_this._33 = cy * cx;

				return *this;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				bool aiMatrix4x4t<TReal>::IsIdentity() const {
				// Use a small epsilon to solve floating-point inaccuracies
				const static TReal epsilon = 10e-3f;

				return (_12 <= epsilon && _12 >= -epsilon &&
					_13 <= epsilon && _13 >= -epsilon &&
					_14 <= epsilon && _14 >= -epsilon &&
					_21 <= epsilon && _21 >= -epsilon &&
					_23 <= epsilon && _23 >= -epsilon &&
					_24 <= epsilon && _24 >= -epsilon &&
					_31 <= epsilon && _31 >= -epsilon &&
					_32 <= epsilon && _32 >= -epsilon &&
					_34 <= epsilon && _34 >= -epsilon &&
					_41 <= epsilon && _41 >= -epsilon &&
					_42 <= epsilon && _42 >= -epsilon &&
					_43 <= epsilon && _43 >= -epsilon &&
					_11 <= 1.f + epsilon && _11 >= 1.f - epsilon &&
					_22 <= 1.f + epsilon && _22 >= 1.f - epsilon &&
					_33 <= 1.f + epsilon && _33 >= 1.f - epsilon &&
					_44 <= 1.f + epsilon && _44 >= 1.f - epsilon);
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::RotationX(TReal a, aiMatrix4x4t<TReal>& out) {
				/*
					 |  1  0       0       0 |
				 M = |  0  cos(A) -sin(A)  0 |
					 |  0  sin(A)  cos(A)  0 |
					 |  0  0       0       1 |  */
				out = aiMatrix4x4t<TReal>();
				out._22 = out._33 = std::cos(a);
				out._23 = -(out._32 = std::sin(a));
				return out;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::RotationY(TReal a, aiMatrix4x4t<TReal>& out) {
				/*
					 |  cos(A)  0   sin(A)  0 |
				 M = |  0       1   0       0 |
					 | -sin(A)  0   cos(A)  0 |
					 |  0       0   0       1 |
					*/
				out = aiMatrix4x4t<TReal>();
				out._11 = out._33 = std::cos(a);
				out._31 = -(out._13 = std::sin(a));
				return out;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::RotationZ(TReal a, aiMatrix4x4t<TReal>& out) {
				/*
					 |  cos(A)  -sin(A)   0   0 |
				 M = |  sin(A)   cos(A)   0   0 |
					 |  0        0        1   0 |
					 |  0        0        0   1 |   */
				out = aiMatrix4x4t<TReal>();
				out._11 = out._22 = std::cos(a);
				out._12 = -(out._21 = std::sin(a));
				return out;
			}

			// ----------------------------------------------------------------------------------------
			// Returns a rotation matrix for a rotation around an arbitrary axis.
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Rotation(TReal a, const aiVector3t<TReal>& axis, aiMatrix4x4t<TReal>& out) {
				TReal c = std::cos(a), s = std::sin(a), t = 1 - c;
				TReal x = axis.x, y = axis.y, z = axis.z;

				// Many thanks to MathWorld and Wikipedia
				out._11 = t * x * x + c;   out._12 = t * x * y - s * z; out._13 = t * x * z + s * y;
				out._21 = t * x * y + s * z; out._22 = t * y * y + c;   out._23 = t * y * z - s * x;
				out._31 = t * x * z - s * y; out._32 = t * y * z + s * x; out._33 = t * z * z + c;
				out._14 = out._24 = out._34 = static_cast<TReal>(0.0);
				out._41 = out._42 = out._43 = static_cast<TReal>(0.0);
				out._44 = static_cast<TReal>(1.0);

				return out;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Translation(const aiVector3t<TReal>& v, aiMatrix4x4t<TReal>& out) {
				out = aiMatrix4x4t<TReal>();
				out._14 = v.x;
				out._24 = v.y;
				out._34 = v.z;
				return out;
			}

			// ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::Scaling(const aiVector3t<TReal>& v, aiMatrix4x4t<TReal>& out) {
				out = aiMatrix4x4t<TReal>();
				out._11 = v.x;
				out._22 = v.y;
				out._33 = v.z;
				return out;
			}

			// ----------------------------------------------------------------------------------------
			/** A function for creating a rotation matrix that rotates a vector called
			 * "from" into another vector called "to".
			 * Input : from[3], to[3] which both must be *normalized* non-zero vectors
			 * Output: mtx[3][3] -- a 3x3 matrix in colum-major form
			 * Authors: Tomas Möller, John Hughes
			 *          "Efficiently Building a Matrix to Rotate One Vector to Another"
			 *          Journal of Graphics Tools, 4(4):1-4, 1999
			 */
			 // ----------------------------------------------------------------------------------------
			template <typename TReal>
			AI_FORCE_INLINE
				aiMatrix4x4t<TReal>& aiMatrix4x4t<TReal>::FromToMatrix(const aiVector3t<TReal>& from,
					const aiVector3t<TReal>& to, aiMatrix4x4t<TReal>& mtx) {
				aiMatrix3x3t<TReal> m3;
				aiMatrix3x3t<TReal>::FromToMatrix(from, to, m3);
				mtx = aiMatrix4x4t<TReal>(m3);
				return mtx;
			}
		}
	}