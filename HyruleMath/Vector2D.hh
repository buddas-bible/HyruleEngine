#pragma once
#include <ostream>
#include <istream>
#include <sal.h>
#include "Define.h"

namespace Hyrule
{
    struct Vector2D
    {
        constexpr Vector2D() noexcept :
#ifdef _PHYSICS
            e{}
#else
            x(), y()
#endif
        {}
        constexpr Vector2D(float _x, float _y) noexcept :
#ifdef _PHYSICS
            e{ _x, _y }
#else
            x(_x), y(_y)
#endif
        {}
        constexpr Vector2D(const Vector2D& other) noexcept = default;
        constexpr Vector2D(Vector2D&& other) noexcept = default;
        constexpr Vector2D(_In_reads_(2) const float* arr) noexcept :
#ifdef _PHYSICS
            e{ arr[0], arr[1] }
#else
            x(arr[0]), y(arr[1])
#endif
        {}
        constexpr Vector2D(const float _n) noexcept :
#ifdef _PHYSICS
            e{ _n, _n }
#else
            x(_n), y(_n)
#endif
        {}

        ~Vector2D() noexcept = default;

        constexpr Vector2D& operator = (const Vector2D&) noexcept = default;
        constexpr Vector2D& operator = (Vector2D&&) noexcept = default;

#ifdef _PHYSICS
        union
        {
            struct
            {
#endif
                float x, y;
#ifdef _PHYSICS	
            };
            float e[2];
        };
#endif
        static constexpr inline Vector2D Zero() noexcept
        {
            return Vector2D();
        }

        /// º¤ÅÍ ÇÔ¼ö
        float Length() const noexcept;
        float LengthSquare() const noexcept;
        float Cross(const Vector2D&) const noexcept;
        float Dot(const Vector2D&) const noexcept;
        float FastInvSqrt(float number) const noexcept;
        Vector2D& Normalize() noexcept;
        Vector2D Normalized() const noexcept;


        /// ¿¬»êÀÚ ¿À¹ö·Îµù
        Vector2D& operator += (const Vector2D&) noexcept;
        Vector2D& operator -= (const Vector2D&) noexcept;

        Vector2D operator + (const Vector2D&) const noexcept;
        Vector2D operator - () const noexcept;
        Vector2D operator - (const Vector2D&) const noexcept;

        Vector2D& operator*= (float) noexcept;
        Vector2D& operator /= (float) noexcept;

        Vector2D operator * (float) noexcept;
        Vector2D operator / (float) noexcept;

        friend Vector2D operator* (float, const Vector2D&) noexcept;	// º¤ÅÍ ½ºÄ®¶ó °ö

        friend std::ostream& operator << (std::ostream& out, const Vector2D& point) noexcept;

        friend std::istream& operator >> (std::istream& in, Vector2D& point) noexcept;

        std::string ToString() noexcept;

        bool operator == (const Vector2D&) const noexcept;			// °°Àº º¤ÅÍÀÎ°¡?
    };
}
