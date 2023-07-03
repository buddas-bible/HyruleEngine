#pragma once

// #include "Vector4D.h"

namespace Hyrule
{
	struct Vector4D;
	struct Matrix1x3;
	struct Matrix3x3;
	struct Quaternion;

	struct Vector3D
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Vector3D() noexcept;
		constexpr Vector3D(float, float, float) noexcept;
		constexpr Vector3D(const Vector3D&) noexcept = default;
		constexpr Vector3D(Vector3D&&) noexcept = default;
		~Vector3D() noexcept = default;
		// explicit operator Vector4D() noexcept;
		constexpr explicit operator Matrix1x3() noexcept;

		constexpr Vector3D& operator= (const Vector3D&) noexcept = default;
		constexpr Vector3D& operator= (Vector3D&&) noexcept = default;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float x, y, z;
			};
			float e[3];
		};

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		Vector3D Cross(const Vector3D&) const noexcept;
		float Dot(const Vector3D&) const noexcept;
		float ScalarTriple(const Vector3D&, const Vector3D&) const noexcept;
		Vector3D VectorTriple(const Vector3D&, const Vector3D&) const noexcept;
		float FastInvSqrt(float) const noexcept;
		Vector3D& Normalize() noexcept;				// ���͸� ����ȭ�ϰ� ��ȯ
		Vector3D Normalized() const noexcept;		// ����ȭ�� ���ο� ���͸� ��ȯ

		static Vector3D Forward();
		static Vector3D Up();
		static Vector3D Right();

		/// <summary>
		/// ������ �����ε�
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

		Vector3D& operator*= (const Matrix3x3&) noexcept;
		Vector3D operator* (const Matrix3x3&) const noexcept;

		bool operator == (const Vector3D&) const noexcept;

		friend Vector3D operator * (const Quaternion&, const Vector3D&) noexcept;
	};

	Vector3D operator * (const Quaternion&, const Vector3D&) noexcept;
}
