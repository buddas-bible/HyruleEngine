#pragma once
#include <ostream>
#include <istream>
#include <sal.h>

#include "Define.h"

namespace Hyrule
{
	struct Matrix1x3;
	struct Matrix3x3;
	struct Matrix4x4;
	struct Quaternion;

	struct Vector3D
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Vector3D() noexcept : 
#ifdef _PHYSICS
            e{}
#else
            x(), y(), z()
#endif
		{}
		constexpr Vector3D(float _x, float _y, float _z) noexcept :
#ifdef _PHYSICS
			e{ _x, _y, _z }
#else
            x(_x), y(_y), z(_z)
#endif
		{}
		constexpr Vector3D(const Vector3D&) noexcept = default;
		constexpr Vector3D(Vector3D&&) noexcept = default;
		constexpr Vector3D(_In_reads_(3) const float* _arr) noexcept :
#ifdef _PHYSICS
			e{ _arr[0], _arr[1], _arr[2] }
#else
            x(_arr[0]), y(_arr[1]), z(_arr[2])
#endif
        {}

        constexpr Vector3D(const float _n) noexcept :
#ifdef _PHYSICS
            e{ _n, _n, _n }
#else
            x(_n), y(_n), z(_n)
#endif
        {}

		~Vector3D() noexcept = default;

		constexpr Vector3D& operator= (const Vector3D&) noexcept = default;
		constexpr Vector3D& operator= (Vector3D&&) noexcept = default;

		explicit operator Matrix1x3() noexcept;

		/// <summary>
		/// ��� ����
		/// </summary>
#ifdef _PHYSICS
		union
		{
			struct
			{
#endif
				float x, y, z;
#ifdef _PHYSICS
			};
		    float e[3];
		};
#endif

		static constexpr inline Vector3D Zero() noexcept
		{
			return Vector3D{};
		}

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

		Vector3D& operator*= (const Matrix4x4&) noexcept;
		Vector3D operator* (const Matrix4x4&) const noexcept;

		bool operator == (const Vector3D&) const noexcept;
        std::string ToString() noexcept;

        friend Vector3D operator * (const Quaternion&, const Vector3D&) noexcept;

        friend std::ostream& operator << (std::ostream& out, const Vector3D& point) noexcept;

        friend std::istream& operator >> (std::istream& in, Vector3D& point) noexcept;
	};
    Vector3D operator * (const Quaternion&, const Vector3D&) noexcept;

}
