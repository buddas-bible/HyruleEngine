#pragma once

#include "Vector4D.h"

namespace Hyrule
{
	struct Vector4D;

	struct Vector3D
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		Vector3D() noexcept;
		Vector3D(float, float, float) noexcept;
		Vector3D(const Vector3D& other) noexcept = default;
		Vector3D(Vector3D&& other) noexcept = default;
		~Vector3D() noexcept = default;
		explicit operator Vector4D();

		Vector3D& operator= (const Vector3D&) noexcept = default;
		Vector3D& operator= (Vector3D&&) noexcept = default;

		/// <summary>
		/// 멤버 변수
		/// </summary>
		float x, y, z;

		/// <summary>
		/// 벡터 함수
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		Vector3D Cross(const Vector3D&) const noexcept;
		float Dot(const Vector3D&) const noexcept;
		float FastInvSqrt(float number) const noexcept;
		Vector3D& Normalize() noexcept;				// 벡터를 정규화하고 반환
		Vector3D Normalized() const noexcept;		// 정규화된 새로운 벡터를 반환

		/// <summary>
		/// 연산자 오버로딩
		/// </summary>
		Vector3D& operator += (const Vector3D&) noexcept;
		Vector3D& operator -= (const Vector3D&) noexcept;

		Vector3D operator + (const Vector3D&) const noexcept;
		Vector3D operator - (const Vector3D&) const noexcept;
		Vector3D operator - () const noexcept;

		Vector3D& operator *= (const float) noexcept;
		Vector3D& operator /= (const float) noexcept;

		Vector3D operator * (const float) const noexcept;
		Vector3D operator / (const float) const noexcept;

		bool operator == (const Vector3D&) const noexcept;
	};

	// Vector3D TripleProduct(const Vector3D& a, const Vector3D& b, const Vector3D& c);
	// Vector3D AxisAndAngleToEuler(const Vector3D& axis, float angle);
}
