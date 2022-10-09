/*
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

/** @file matrix3x3.h
 *  @brief Definition of a 3x3 matrix, including operators when compiling in C++
 */
#pragma once
#include "DLLDefine.h"

namespace Engine
{
    namespace Type
    {
        template <typename T> class Matrix4x4t;
        template <typename T> class Vector2t;
        template <typename T> class Vector3t;

        // ---------------------------------------------------------------------------
        /** @brief Represents a row-major 3x3 matrix
         *
         *  There's much confusion about matrix layouts (column vs. row order).
         *  This is *always* a row-major matrix. Not even with the
         *  #aiProcess_ConvertToLeftHanded flag, which absolutely does not affect
         *  matrix order - it just affects the handedness of the coordinate system
         *  defined thereby.
         */
        template <typename TReal>
        class ENGINE_API Matrix3x3t {
        public:
            Matrix3x3t() noexcept :
                _11(static_cast<TReal>(1.0f)), _12(), _13(),
                _21(), _22(static_cast<TReal>(1.0f)), _23(),
                _31(), _32(), _33(static_cast<TReal>(1.0f)) {}

            Matrix3x3t(TReal m00, TReal m01, TReal m02,
                TReal m10, TReal m11, TReal m12,
                TReal m20, TReal m21, TReal m22) :
                _11(m00), _12(m01), _13(m02),
                _21(m10), _22(m11), _23(m12),
                _31(m20), _32(m21), _33(m22)
            {}

            // matrix multiplication.
            Matrix3x3t& operator *= (const Matrix3x3t& m)
            {
                *this = Matrix3x3t<TReal>(m._11 * _11 + m._21 * _12 + m._31 * _13,
                    m._12 * _11 + m._22 * _12 + m._32 * _13,
                    m._13 * _11 + m._23 * _12 + m._33 * _13,
                    m._11 * _21 + m._21 * _22 + m._31 * _23,
                    m._12 * _21 + m._22 * _22 + m._32 * _23,
                    m._13 * _21 + m._23 * _22 + m._33 * _23,
                    m._11 * _31 + m._21 * _32 + m._31 * _33,
                    m._12 * _31 + m._22 * _32 + m._32 * _33,
                    m._13 * _31 + m._23 * _32 + m._33 * _33);
                return *this;
            }
            Matrix3x3t  operator  * (const Matrix3x3t& m) const
            {
                Matrix3x3t<TReal> temp(*this);
                temp *= m;
                return temp;
            }

            // array access operators
            TReal* operator[]       (unsigned int p_iIndex)
            {
                switch (p_iIndex) {
                case 0:
                    return &_11;
                case 1:
                    return &_21;
                case 2:
                    return &_31;
                default:
                    break;
                }
                return &_11;
            }
            const TReal* operator[] (unsigned int p_iIndex) const
            {
                switch (p_iIndex) {
                case 0:
                    return &_11;
                case 1:
                    return &_21;
                case 2:
                    return &_31;
                default:
                    break;
                }
                return &_11;
            }

            // comparison operators
            bool operator== (const Matrix3x3t<TReal>& m) const
            {
                return _11 == m._11 && _12 == m._12 && _13 == m._13 &&
                    _21 == m._21 && _22 == m._22 && _23 == m._23 &&
                    _31 == m._31 && _32 == m._32 && _33 == m._33;
            }
            bool operator!= (const Matrix3x3t<TReal>& m) const
            {
                return !(*this == m);
            }

            bool Equal(const Matrix3x3t<TReal>& m, TReal epsilon = std::numeric_limits<TReal>::epsilon()) const
            {
                std::abs(_11 - m._11) <= epsilon &&
                    std::abs(_12 - m._12) <= epsilon &&
                    std::abs(_13 - m._13) <= epsilon &&
                    std::abs(_21 - m._21) <= epsilon &&
                    std::abs(_22 - m._22) <= epsilon &&
                    std::abs(_23 - m._23) <= epsilon &&
                    std::abs(_31 - m._31) <= epsilon &&
                    std::abs(_32 - m._32) <= epsilon &&
                    std::abs(_33 - m._33) <= epsilon;
            }

            template <typename TOther>
            operator Matrix3x3t<TOther>() const
            {
                return Matrix3x3t<TOther>(static_cast<TOther>(_11), static_cast<TOther>(_12), static_cast<TOther>(_13),
                    static_cast<TOther>(_21), static_cast<TOther>(_22), static_cast<TOther>(_23),
                    static_cast<TOther>(_31), static_cast<TOther>(_32), static_cast<TOther>(_33));
            }

            // -------------------------------------------------------------------
            /** @brief Construction from a 4x4 matrix. The remaining parts
             *  of the matrix are ignored.
             */
            explicit Matrix3x3t(const Matrix4x4t<TReal>& pMatrix)
            {
                _11 = pMatrix._11; _12 = pMatrix._12; _13 = pMatrix._13;
                _21 = pMatrix._21; _22 = pMatrix._22; _23 = pMatrix._23;
                _31 = pMatrix._31; _32 = pMatrix._32; _33 = pMatrix._33;
            }

            // -------------------------------------------------------------------
            /** @brief Transpose the matrix
             */
            Matrix3x3t& Transpose()
            {
                // (TReal&) don't remove, GCC complains cause of packed fields
                std::swap((TReal&)_12, (TReal&)_21);
                std::swap((TReal&)_13, (TReal&)_31);
                std::swap((TReal&)_23, (TReal&)_32);
                return *this;
            }

            // -------------------------------------------------------------------
            /** @brief Invert the matrix.
             *  If the matrix is not invertible all elements are set to qnan.
             *  Beware, use (f != f) to check whether a TReal f is qnan.
             */
            Matrix3x3t& Inverse()
            {
                // Compute the reciprocal determinant
                TReal det = Determinant();
                if (det == static_cast<TReal>(0.0))
                {
                    // Matrix not invertible. Setting all elements to nan is not really
                    // correct in a mathematical sense; but at least qnans are easy to
                    // spot. XXX we might throw an exception instead, which would
                    // be even much better to spot :/.
                    const TReal nan = std::numeric_limits<TReal>::quiet_NaN();
                    *this = Matrix3x3t<TReal>(nan, nan, nan, nan, nan, nan, nan, nan, nan);

                    return *this;
                }

                TReal invdet = static_cast<TReal>(1.0) / det;

                Matrix3x3t<TReal> res;
                res._11 = invdet * (_22 * _33 - _23 * _32);
                res._12 = -invdet * (_12 * _33 - _13 * _32);
                res._13 = invdet * (_12 * _23 - _13 * _22);
                res._21 = -invdet * (_21 * _33 - _23 * _31);
                res._22 = invdet * (_11 * _33 - _13 * _31);
                res._23 = -invdet * (_11 * _23 - _13 * _21);
                res._31 = invdet * (_21 * _32 - _22 * _31);
                res._32 = -invdet * (_11 * _32 - _12 * _31);
                res._33 = invdet * (_11 * _22 - _12 * _21);
                *this = res;

                return *this;
            }
            TReal Determinant() const
            {
                return _11 * _22 * _33 - _11 * _23 * _32 + _12 * _23 * _31 - _12 * _21 * _33 + _13 * _21 * _32 - _13 * _22 * _31;
            }

            // -------------------------------------------------------------------
            /** @brief Returns a rotation matrix for a rotation around z
             *  @param a Rotation angle, in radians
             *  @param out Receives the output matrix
             *  @return Reference to the output matrix
             */
            static Matrix3x3t& RotationZ(TReal a, Matrix3x3t& out)
            {
                out._11 = out._22 = std::cos(a);
                out._21 = std::sin(a);
                out._12 = -out._21;

                out._13 = out._23 = out._31 = out._32 = 0.f;
                out._33 = 1.f;

                return out;
            }

            // -------------------------------------------------------------------
            /** @brief Returns a rotation matrix for a rotation around
             *    an arbitrary axis.
             *
             *  @param a Rotation angle, in radians
             *  @param axis Axis to rotate around
             *  @param out To be filled
             */
            static Matrix3x3t& Rotation(TReal a, const Vector3t<TReal>& axis, Matrix3x3t& out)
            {
                TReal c = std::cos(a), s = std::sin(a), t = 1 - c;
                TReal x = axis.x, y = axis.y, z = axis.z;

                // Many thanks to MathWorld and Wikipedia
                out._11 = t * x * x + c;   out._12 = t * x * y - s * z; out._13 = t * x * z + s * y;
                out._21 = t * x * y + s * z; out._22 = t * y * y + c;   out._23 = t * y * z - s * x;
                out._31 = t * x * z - s * y; out._32 = t * y * z + s * x; out._33 = t * z * z + c;

                return out;
            }

            // -------------------------------------------------------------------
            /** @brief Returns a translation matrix
             *  @param v Translation vector
             *  @param out Receives the output matrix
             *  @return Reference to the output matrix
             */
            static Matrix3x3t& Translation(const Vector2t<TReal>& v, Matrix3x3t& out)
            {
                out = Matrix3x3t<TReal>();
                out._13 = v.x;
                out._23 = v.y;
                return out;
            }

            // -------------------------------------------------------------------
            /** @brief A function for creating a rotation matrix that rotates a
             *  vector called "from" into another vector called "to".
             * Input : from[3], to[3] which both must be *normalized* non-zero vectors
             * Output: mtx[3][3] -- a 3x3 matrix in column-major form
             * Authors: Tomas Möller, John Hughes
             *          "Efficiently Building a Matrix to Rotate One Vector to Another"
             *          Journal of Graphics Tools, 4(4):1-4, 1999
             */
            static Matrix3x3t& FromToMatrix(const Vector3t<TReal>& from,
                const Vector3t<TReal>& to, Matrix3x3t& out)
            {
                const TReal e = from * to;
                const TReal f = (e < 0) ? -e : e;

                if (f > static_cast<TReal>(1.0) - static_cast<TReal>(0.00001))     /* "from" and "to"-vector almost parallel */
                {
                    Vector3f u, v;     /* temporary storage vectors */
                    Vector3f x;       /* vector most nearly orthogonal to "from" */

                    x.x = (from.x > 0.0) ? from.x : -from.x;
                    x.y = (from.y > 0.0) ? from.y : -from.y;
                    x.z = (from.z > 0.0) ? from.z : -from.z;

                    if (x.x < x.y)
                    {
                        if (x.x < x.z)
                        {
                            x.x = static_cast<TReal>(1.0);
                            x.y = x.z = static_cast<TReal>(0.0);
                        }
                        else
                        {
                            x.z = static_cast<TReal>(1.0);
                            x.x = x.y = static_cast<TReal>(0.0);
                        }
                    }
                    else
                    {
                        if (x.y < x.z)
                        {
                            x.y = static_cast<TReal>(1.0);
                            x.x = x.z = static_cast<TReal>(0.0);
                        }
                        else
                        {
                            x.z = static_cast<TReal>(1.0);
                            x.x = x.y = static_cast<TReal>(0.0);
                        }
                    }

                    u.x = x.x - from.x; u.y = x.y - from.y; u.z = x.z - from.z;
                    v.x = x.x - to.x;   v.y = x.y - to.y;   v.z = x.z - to.z;
                    
                    const TReal _31_ = static_cast<TReal>(2.0) / (u * u);
                    const TReal _32_ = static_cast<TReal>(2.0) / (v * v);
                    const TReal _33_ = _31_ * _32_ * (u * v);

                    for (unsigned int i = 0; i < 3; i++)
                    {
                        for (unsigned int j = 0; j < 3; j++)
                        {
                            out[i][j] = -_31_ * u[i] * u[j] - _32_ * v[i] * v[j]
                                + _33_ * v[i] * u[j];
                        }
                        out[i][i] += static_cast<TReal>(1.0);
                    }
                }
                else  /* the most common case, unless "from"="to", or "from"=-"to" */
                {
                    const Vector3f v = from ^ to;
                    /* ... use this hand optimized version (9 mults less) */
                    const TReal h = static_cast<TReal>(1.0) / (static_cast<TReal>(1.0) + e);      /* optimization by Gottfried Chen */
                    const TReal hvx = h * v.x;
                    const TReal hvz = h * v.z;
                    const TReal hvxy = hvx * v.y;
                    const TReal hvxz = hvx * v.z;
                    const TReal hvyz = hvz * v.y;
                    out[0][0] = e + hvx * v.x;
                    out[0][1] = hvxy - v.z;
                    out[0][2] = hvxz + v.y;

                    out[1][0] = hvxy + v.z;
                    out[1][1] = e + h * v.y * v.y;
                    out[1][2] = hvyz - v.x;

                    out[2][0] = hvxz - v.y;
                    out[2][1] = hvyz + v.x;
                    out[2][2] = e + hvz * v.z;
                }
                return out;
            }

        public:
            TReal _11, _12, _13;
            TReal _21, _22, _23;
            TReal _31, _32, _33;
        };

        typedef Matrix3x3t<float> Matrix3x3f;
        typedef Matrix3x3t<double> Matrix3x3d;






    }
}

