#pragma once

namespace Engine
{
    namespace Type
    {
        // ---------------------------------------------------------------------------
/// @brief  Represents a three-dimensional vector.
// ---------------------------------------------------------------------------
        template <typename TReal>
        class aiVector3t {
        public:
            /// @brief  The default class constructor.
            aiVector3t() AI_NO_EXCEPT : x(), y(), z() {}

            /// @brief  The class constructor with the components.
            /// @param  _x  The x-component for the vector.
            /// @param  _y  The y-component for the vector.
            /// @param  _z  The z-component for the vector.
            aiVector3t(TReal _x, TReal _y, TReal _z) : x(_x), y(_y), z(_z) {}

            /// @brief  The class constructor with a default value.
            /// @param  _xyz  The value for x, y and z.
            explicit aiVector3t(TReal _xyz) : x(_xyz), y(_xyz), z(_xyz) {}

            /// @brief  The copy constructor.
            /// @param  o The instance to copy from.
            aiVector3t(const aiVector3t& o) = default;

            /// @brief  combined operators
            /// @brief  The copy constructor.
            const aiVector3t& operator += (const aiVector3t& o);

            /// @brief  The copy constructor.
            const aiVector3t& operator -= (const aiVector3t& o);

            /// @brief  The copy constructor.
            const aiVector3t& operator *= (TReal f);

            /// @brief  The copy constructor.
            const aiVector3t& operator /= (TReal f);

            /// @brief  Transform vector by matrix
            aiVector3t& operator *= (const aiMatrix3x3t<TReal>& mat);
            aiVector3t& operator *= (const aiMatrix4x4t<TReal>& mat);

            /// @brief  access a single element, const.
            TReal operator[](unsigned int i) const;

            /// @brief  access a single element, non-const.
            TReal& operator[](unsigned int i);

            // comparison
            bool operator== (const aiVector3t& other) const;
            bool operator!= (const aiVector3t& other) const;
            bool operator < (const aiVector3t& other) const;

            /// @brief  
            bool Equal(const aiVector3t& other, TReal epsilon = ai_epsilon) const;

            template <typename TOther>
            operator aiVector3t<TOther>() const;

            /** @brief Set the components of a vector
             *  @param pX X component
             *  @param pY Y component
             *  @param pZ Z component  */
            void Set(TReal pX, TReal pY, TReal pZ);

            /** @brief Get the squared length of the vector
             *  @return Square length */
            TReal SquareLength() const;

            /** @brief Get the length of the vector
             *  @return length */
            TReal Length() const;


            /** @brief Normalize the vector */
            aiVector3t& Normalize();

            /** @brief Normalize the vector with extra check for zero vectors */
            aiVector3t& NormalizeSafe();

            /** @brief Componentwise multiplication of two vectors
             *
             *  Note that vec*vec yields the dot product.
             *  @param o Second factor */
            const aiVector3t SymMul(const aiVector3t& o);

            TReal x, y, z;
        };


        typedef aiVector3t<ai_real> aiVector3D;
    }
}

template<typename TReal> class aiMatrix3x3t;
template<typename TReal> class aiMatrix4x4t;
