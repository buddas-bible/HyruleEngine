#pragma once
#include "Vector3D.h"

namespace Hyrule
{
	struct Vector3D;

	struct Vector4D
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		Vector4D() noexcept;
		Vector4D(float, float, float, float) noexcept;
		Vector4D(const Vector4D& other) noexcept = default;
		Vector4D(Vector4D&& other) noexcept = default;
		~Vector4D() noexcept = default;
		explicit operator Vector3D();

		Vector4D& operator= (const Vector4D&) noexcept = default;
		Vector4D& operator= (Vector4D&&) noexcept = default;

		/// <summary>
		/// 멤버 변수
		/// </summary>
		// union
		// {
		// 	float e[4];
		// 	struct  
		// 	{
				float x, y, z, w;
		// 	};
		// };;

		/// <summary>
		/// 벡터 함수
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		Vector4D Cross(const Vector4D&) const noexcept;
		float Dot(const Vector4D&) const noexcept;
		float FastInvSqrt(float number) const noexcept;
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

		Vector4D& operator *= (const float) noexcept;
		Vector4D& operator /= (const float) noexcept;

		Vector4D operator * (const float) const noexcept;
		Vector4D operator / (const float) const noexcept;

		bool operator == (const Vector4D&) const noexcept;
	};

	// Vector3D TripleProduct(const Vector3D& a, const Vector3D& b, const Vector3D& c);
	// Vector3D AxisAndAngleToEuler(const Vector3D& axis, float angle);
}
