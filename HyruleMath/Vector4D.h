#pragma once
// #include <xmmintrin.h>
#include <smmintrin.h>
// #include "Vector3D.h"

namespace Hyrule
{
	struct Vector3D;
	struct Matrix1x4;
	struct Quaternion;

	struct Vector4D
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		constexpr Vector4D() noexcept;
		constexpr Vector4D(float, float, float, float) noexcept;
		constexpr Vector4D(const Vector4D& other) noexcept = default;
		constexpr Vector4D(Vector4D&& other) noexcept = default;
		constexpr Vector4D(const Vector3D&, float) noexcept;
		~Vector4D() noexcept = default;
		constexpr explicit operator Matrix1x4() noexcept;
		constexpr explicit operator Quaternion() noexcept;

		constexpr Vector4D& operator= (const Vector4D&) noexcept = default;
		constexpr Vector4D& operator= (Vector4D&&) noexcept = default;

		/// <summary>
		/// 멤버 변수
		/// </summary>
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float e[4];
			__m128 m;
		};;

		static inline Vector4D Zero() noexcept
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

		bool operator == (const Vector4D&) const noexcept;
	};
}
