#pragma once
#include "DLLDefine.h"

namespace Engine
{
	namespace Type
	{
        //assimp에서 따왔다고 명시하기

        template <typename TReal>
        class FVector2 {
        public:
            FVector2() : x(), y() {}
            FVector2(TReal _x, TReal _y) : x(_x), y(_y) {}
            explicit FVector2(TReal _xyz) : x(_xyz), y(_xyz) {}
            FVector2(const FVector2& o) = default;

            void Set(TReal pX, TReal pY);
            FVector2 SquareLength() const;
            FVector2 Length() const;
            FVector2& Normalize();

            const FVector2& operator += (const FVector2& o);
            const FVector2& operator -= (const FVector2& o);
            const FVector2& operator *= (TReal f);
            const FVector2& operator /= (TReal f);

            TReal operator[](unsigned int i) const;

            bool operator== (const FVector2& other) const;
            bool operator!= (const FVector2& other) const;

            //bool Equal(const FVector2& other, TReal epsilon = ai_epsilon) const;

            FVector2& operator= (TReal f);
            const FVector2 SymMul(const FVector2& o);

            template <typename TOther>
            operator FVector2<TOther>() const;

            TReal x, y;
        };

        typedef FVector2<float> FVector2f;
        typedef FVector2<double> FVector2d;
        typedef FVector2<int> FVector2i;


	}
}
