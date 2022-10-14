/*
Open Asset Import Library (assimp)
----------------------------------------------------------------------

Copyright (c) 2006-2022, assimp team


All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:

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

----------------------------------------------------------------------
*/

/** @file quaternion.h
 *  @brief Quaternion structure, including operators when compiling in C++
 */
#pragma once
#include "DLLDefine.h"

namespace Engine
{
    namespace Type
    {
        template <typename TReal> class Vector3t;
        template <typename TReal> class Matrix3x3t;
        template <typename TReal> class Matrix4x4t;

        // ---------------------------------------------------------------------------
        /** Represents a quaternion in a 4D vector. */
        template <typename TReal>
        class ENGINE_API Quaterniont
        {
        public:
            Quaterniont() noexcept : w(1.0), x(), y(), z() {}
            Quaterniont(TReal pw, TReal px, TReal py, TReal pz)
                : w(pw), x(px), y(py), z(pz) {}

            /** Construct from rotation matrix. Result is undefined if the matrix is not orthonormal. */
            explicit Quaterniont(const Matrix3x3t<TReal>& pRotMatrix)
            {
                TReal t = pRotMatrix._11 + pRotMatrix._22 + pRotMatrix._33;

                // large enough
                if (t > static_cast<TReal>(0))
                {
                    TReal s = std::sqrt(1 + t) * static_cast<TReal>(2.0);
                    x = (pRotMatrix._23 - pRotMatrix._32) / s;
                    y = (pRotMatrix._31 - pRotMatrix._13) / s;
                    z = (pRotMatrix._12 - pRotMatrix._21) / s;
                    w = static_cast<TReal>(0.25) * s;
                } // else we have to check several cases
                else if (pRotMatrix._11 > pRotMatrix._22 && pRotMatrix._11 > pRotMatrix._33)
                {
                    // Column 0:
                    TReal s = std::sqrt(static_cast<TReal>(1.0) + pRotMatrix._11 - pRotMatrix._22 - pRotMatrix._33) * static_cast<TReal>(2.0);
                    x = static_cast<TReal>(0.25) * s;
                    y = (pRotMatrix._12 + pRotMatrix._21) / s;
                    z = (pRotMatrix._31 + pRotMatrix._13) / s;
                    w = (pRotMatrix._23 - pRotMatrix._32) / s;
                }
                else if (pRotMatrix._22 > pRotMatrix._33)
                {
                    // Column 1:
                    TReal s = std::sqrt(static_cast<TReal>(1.0) + pRotMatrix._22 - pRotMatrix._11 - pRotMatrix._33) * static_cast<TReal>(2.0);
                    x = (pRotMatrix._12 + pRotMatrix._21) / s;
                    y = static_cast<TReal>(0.25) * s;
                    z = (pRotMatrix._23 + pRotMatrix._32) / s;
                    w = (pRotMatrix._31 - pRotMatrix._13) / s;
                }
                else
                {
                    // Column 2:
                    TReal s = std::sqrt(static_cast<TReal>(1.0) + pRotMatrix._33 - pRotMatrix._11 - pRotMatrix._22) * static_cast<TReal>(2.0);
                    x = (pRotMatrix._31 + pRotMatrix._13) / s;
                    y = (pRotMatrix._23 + pRotMatrix._32) / s;
                    z = static_cast<TReal>(0.25) * s;
                    w = (pRotMatrix._12 - pRotMatrix._21) / s;
                }
            }

            /** Construct from euler angles */
            Quaterniont(TReal roty, TReal rotz, TReal rotx)
            {
                const TReal fSinPitch(std::sin(rotx * static_cast<TReal>(0.5)));
                const TReal fCosPitch(std::cos(rotx * static_cast<TReal>(0.5)));
                const TReal fSinYaw(std::sin(roty * static_cast<TReal>(0.5)));
                const TReal fCosYaw(std::cos(roty * static_cast<TReal>(0.5)));
                const TReal fSinRoll(std::sin(rotz * static_cast<TReal>(0.5)));
                const TReal fCosRoll(std::cos(rotz * static_cast<TReal>(0.5)));
                const TReal fCosPitchCosYaw(fCosPitch * fCosYaw);
                const TReal fSinPitchSinYaw(fSinPitch * fSinYaw);
                x = fSinRoll * fCosPitchCosYaw - fCosRoll * fSinPitchSinYaw;
                y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
                z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
                w = fCosRoll * fCosPitchCosYaw + fSinRoll * fSinPitchSinYaw;
            }

            /** Construct from an axis-angle pair */
            Quaterniont(Vector3t<TReal> axis, TReal angle)
            {
                axis.Normalize();

                const TReal sin_a = std::sin(angle / 2);
                const TReal cos_a = std::cos(angle / 2);
                x = axis.x * sin_a;
                y = axis.y * sin_a;
                z = axis.z * sin_a;
                w = cos_a;
            }

            /** Construct from a normalized quaternion stored in a ve_33 */
            explicit Quaterniont(Vector3t<TReal> normalized)
            {
                x = normalized.x;
                y = normalized.y;
                z = normalized.z;

                const TReal t = static_cast<TReal>(1.0) - (x * x) - (y * y) - (z * z);

                if (t < static_cast<TReal>(0.0)) {
                    w = static_cast<TReal>(0.0);
                }
                else w = std::sqrt(t);
            }

            /** Returns a matrix representation of the quaternion */
            Matrix3x3t<TReal> GetMatrix() const
            {
                Matrix3x3t<TReal> resMatrix;
                resMatrix._11 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (y * y + z * z);
                resMatrix._21 = static_cast<TReal>(2.0) * (x * y - z * w);
                resMatrix._31 = static_cast<TReal>(2.0) * (x * z + y * w);
                resMatrix._12 = static_cast<TReal>(2.0) * (x * y + z * w);
                resMatrix._22 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + z * z);
                resMatrix._32 = static_cast<TReal>(2.0) * (y * z - x * w);
                resMatrix._13 = static_cast<TReal>(2.0) * (x * z - y * w);
                resMatrix._23 = static_cast<TReal>(2.0) * (y * z + x * w);
                resMatrix._33 = static_cast<TReal>(1.0) - static_cast<TReal>(2.0) * (x * x + y * y);

                return resMatrix;
            }

        public:
            bool operator== (const Quaterniont& o) const
            {
                return x == o.x && y == o.y && z == o.z && w == o.w;
            }
            bool operator!= (const Quaterniont& o) const
            {
                return !(*this == o);
            }

            // transform vector by matrix
            Quaterniont& operator *= (const Matrix4x4t<TReal>& mat)
            {
                return (*this = mat * (*this));
            }

            bool Equal(const Quaterniont& o, TReal epsilon = std::numeric_limits<TReal>::epsilon()) const
            {
                return
                    std::abs(x - o.x) <= epsilon &&
                    std::abs(y - o.y) <= epsilon &&
                    std::abs(z - o.z) <= epsilon &&
                    std::abs(w - o.w) <= epsilon;
            }

        public:

            /** Normalize the quaternion */
            Quaterniont& Normalize()
            {
                // compute the magnitude and divide through it
                const TReal mag = std::sqrt(x * x + y * y + z * z + w * w);
                if (mag)
                {
                    const TReal invMag = static_cast<TReal>(1.0) / mag;
                    x *= invMag;
                    y *= invMag;
                    z *= invMag;
                    w *= invMag;
                }
                return *this;
            }

            /** Compute quaternion conjugate */
            Quaterniont& Conjugate()
            {
                x = -x;
                y = -y;
                z = -z;
                return *this;
            }

            /** Rotate a point by this quaternion */
            Vector3t<TReal> Rotate(const Vector3t<TReal>& in) const
            {
                Quaterniont q2(0.f, in.x, in.y, in.z), q = *this, qinv = q;
                qinv.Conjugate();

                q = q * q2 * qinv;
                return Vector3t<TReal>(q.x, q.y, q.z);
            }

            /** Multiply two quaternions */
            Quaterniont operator* (const Quaterniont& t) const
            {
                return Quaterniont(w * t.w - x * t.x - y * t.y - z * t.z,
                    w * t.x + x * t.w + y * t.z - z * t.y,
                    w * t.y + y * t.w + z * t.x - x * t.z,
                    w * t.z + z * t.w + x * t.y - y * t.x);
            }

        public:

            /** Performs a spherical interpolation between two quaternions and writes the result into the third.
             * @param pOut Target object to received the interpolated rotation.
             * @param pStart Start rotation of the interpolation at factor == 0.
             * @param pEnd End rotation, factor == 1.
             * @param pFactor Interpolation factor between 0 and 1. Values outside of this range yield undefined results.
             */
            static void Interpolate(Quaterniont& pOut, const Quaterniont& pStart,
                const Quaterniont& pEnd, TReal pFactor)
            {
                // calc cosine theta
                TReal cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

                // adjust signs (if necessary)
                Quaterniont end = pEnd;
                if (cosom < static_cast<TReal>(0.0))
                {
                    cosom = -cosom;
                    end.x = -end.x;   // Reverse all signs
                    end.y = -end.y;
                    end.z = -end.z;
                    end.w = -end.w;
                }

                // Calculate coefficients
                TReal sclp, sclq;
                if ((static_cast<TReal>(1.0) - cosom) > static_cast<TReal>(0.0001)) // 0.0001 -> some epsillon
                {
                    // Standard case (slerp)
                    TReal omega, sinom;
                    omega = std::acos(cosom); // extract theta from dot product's cos theta
                    sinom = std::sin(omega);
                    sclp = std::sin((static_cast<TReal>(1.0) - pFactor) * omega) / sinom;
                    sclq = std::sin(pFactor * omega) / sinom;
                }
                else
                {
                    // Very close, do linear interp (because it's faster)
                    sclp = static_cast<TReal>(1.0) - pFactor;
                    sclq = pFactor;
                }

                pOut.x = sclp * pStart.x + sclq * end.x;
                pOut.y = sclp * pStart.y + sclq * end.y;
                pOut.z = sclp * pStart.z + sclq * end.z;
                pOut.w = sclp * pStart.w + sclq * end.w;
            }

        public:

            //! w,x,y,z components of the quaternion
            TReal w, x, y, z;
        };

        typedef Quaterniont<float> Quaternionf;
        typedef Quaterniont<double> Quaterniond;

        // ------------------------------------------------------------------------------------------------
/** Transformation of a quaternion by a 4x4 matrix */
        template <typename TReal>
        inline
            Quaterniont<TReal> operator * (const Matrix4x4t<TReal>& pMatrix, const Quaterniont<TReal>& pQuaternion) {
            Quaterniont<TReal> res;
            res.x = pMatrix._11 * pQuaternion.x + pMatrix._21 * pQuaternion.y + pMatrix._31 * pQuaternion.z + pMatrix.a4 * pQuaternion.w;
            res.y = pMatrix._12 * pQuaternion.x + pMatrix._22 * pQuaternion.y + pMatrix._32 * pQuaternion.z + pMatrix.b4 * pQuaternion.w;
            res.z = pMatrix._13 * pQuaternion.x + pMatrix._23 * pQuaternion.y + pMatrix._33 * pQuaternion.z + pMatrix.c4 * pQuaternion.w;
            res.w = pMatrix.d1 * pQuaternion.x + pMatrix.d2 * pQuaternion.y + pMatrix.d3 * pQuaternion.z + pMatrix.d4 * pQuaternion.w;
            return res;
        }        
    }
}


