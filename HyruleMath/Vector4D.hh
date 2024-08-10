#pragma once
#include <ostream>
#include <istream>
#include <smmintrin.h>
#include <sal.h>

#include "Define.h"

// #define _CLIENT

namespace Hyrule
{
	struct Vector3D;
	struct Matrix1x4;
	struct Matrix4x4;
	struct Quaternion;

	struct Vector4D
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		constexpr Vector4D() noexcept :
#ifdef _PHYSICS
			e{}
#else
            x(), y(), z(), w()
#endif
		{}

#ifdef _PHYSICS
		constexpr Vector4D(__m128 _m) noexcept :
			m{ _m }
		{}
#endif

        constexpr Vector4D(float _x, float _y, float _z, float _w) noexcept :
#ifdef _PHYSICS
            e{ _x, _y, _z, _w }
#else
            x(_x), y(_y), z(_z), w(_w)
#endif
		{}
		constexpr Vector4D(const Vector4D& other) noexcept = default;
		constexpr Vector4D(Vector4D&& other) noexcept = default;
		constexpr Vector4D(_In_reads_(4) const float* _arr) noexcept :
#ifdef _PHYSICS
			e{ _arr[0], _arr[1], _arr[2], _arr[3] }
#else
            x(_arr[0]), y(_arr[1]), z(_arr[2]), w(_arr[3])
#endif
        {}

		Vector4D(const Vector3D&, const float) noexcept;
        constexpr Vector4D(const float _n) noexcept :
#ifdef _PHYSICS
            e{ _n, _n, _n, _n }
#else
            x(_n), y(_n), z(_n), w(_n)
#endif
        {}

		~Vector4D() noexcept = default;

		constexpr Vector4D& operator= (const Vector4D&) noexcept = default;
		constexpr Vector4D& operator= (Vector4D&&) noexcept = default;

		explicit operator Matrix1x4() noexcept;
		explicit operator Quaternion() noexcept;

		/// <summary>
		/// 멤버 변수
		/// </summary>
#ifdef _PHYSICS
		union
		{
			struct
			{
#endif
				float x, y, z, w;
#ifdef _PHYSICS
            };
		    float e[4];
		    __m128 m;
		};;
#endif

		static constexpr inline Vector4D Zero() noexcept
		{
			return Vector4D{};
		}

		/// <summary>
		/// 벡터 함수
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		Vector4D Cross(const Vector4D&) const noexcept;
		float Dot(const Vector4D&) const noexcept;
		float FastInvSqrt(float) const noexcept;			// 사실 이 함수는 여기에 없어야할 거 같은데..
		Vector4D& Normalize() noexcept;
		Vector4D Normalized() const noexcept;
		
		// Vector3D 방식으로 처리하고 싶을 때
		float Dot3(const Vector4D&) const noexcept;
		Vector4D& Normalize3() noexcept;
		Vector4D Normalized3() const noexcept;

		/// <summary>
		/// 연산자 오버로딩
		/// </summary>
		Vector4D& operator += (const Vector4D&) noexcept;
		Vector4D& operator -= (const Vector4D&) noexcept;

		Vector4D operator + (const Vector4D&) const noexcept;
		Vector4D operator - (const Vector4D&) const noexcept;
		Vector4D operator - () const noexcept;

		Vector4D& operator *= (const float) noexcept;
		Vector4D& operator /= (const float) noexcept;

		Vector4D operator * (const float) const noexcept;
		Vector4D operator / (const float) const noexcept;

		Vector4D& operator *= (const Matrix4x4&) noexcept;
		Vector4D operator * (const Matrix4x4&) const noexcept;

		bool operator == (const Vector4D&) const noexcept;
        std::string ToString() noexcept;

        friend std::ostream& operator << (std::ostream& out, const Vector4D& point) noexcept;

        friend std::istream& operator >> (std::istream& in, Vector4D& point) noexcept;
	};
}
