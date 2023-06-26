#pragma once
#include <emmintrin.h>

namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix1x4;
	struct Matrix4x4;

	struct Quaternion
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Quaternion() noexcept;
		constexpr Quaternion(float, float, float, float) noexcept;
		constexpr Quaternion(const Quaternion&) noexcept = default;
		constexpr Quaternion(Quaternion&&) noexcept = default;
		~Quaternion() noexcept = default;

		constexpr Quaternion& operator= (const Quaternion&) noexcept = default;
		constexpr Quaternion& operator= (Quaternion&&) noexcept = default;

		constexpr explicit operator Matrix1x4() noexcept;
		constexpr explicit operator Vector4D() noexcept;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float w, x, y, z;
			};
			float e[4];
			__m128 m;
		};

		static inline Quaternion Identity() noexcept
		{
			return Quaternion{ 1.f, 0.f, 0.f, 0.f };
		}

		/// <summary>
		/// ���ʹϾ� �Լ�
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		float FastInvSqrt(float) const noexcept;
		float Dot(const Quaternion&) const noexcept;

		Quaternion Conjugate() const noexcept;
		Quaternion Inverse() const noexcept;
		Quaternion& Normalize() noexcept;
		Quaternion Normalized() const noexcept;

		// ���� �Լ� �������� �ñ� ����
		Vector3D ToEuler() const noexcept;
		Vector4D ToAxisAngle() const noexcept;
		Matrix4x4 ToMatrix() const noexcept;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Quaternion& operator += (const Quaternion&) noexcept;
		Quaternion& operator -= (const Quaternion&) noexcept;

		Quaternion operator + (const Quaternion&) const noexcept;
		Quaternion operator - (const Quaternion&) const noexcept;
		Quaternion operator - () const noexcept;

		Quaternion& operator *= (const Quaternion&) noexcept;
		Quaternion& operator /= (const Quaternion&) noexcept;

		Quaternion operator * (const Quaternion&) const noexcept;
		Quaternion operator / (const Quaternion&) const noexcept;

		Quaternion& operator *= (const float) noexcept;
		Quaternion& operator /= (const float) noexcept;

		Quaternion operator * (const float) const noexcept;
		Quaternion operator / (const float) const noexcept;

		friend Quaternion operator *= (const float, const Quaternion&) noexcept;
		friend Quaternion operator /= (const float, const Quaternion&) noexcept;

		friend Quaternion operator * (const float, const Quaternion&) noexcept;
		friend Quaternion operator / (const float, const Quaternion&) noexcept;

		bool operator == (const Quaternion&) const noexcept;
	};

	Quaternion operator *= (const float, const Quaternion&) noexcept;
	Quaternion operator /= (const float, const Quaternion&) noexcept;
	Quaternion operator * (const float, const Quaternion&) noexcept;
	Quaternion operator / (const float, const Quaternion&) noexcept;
}

