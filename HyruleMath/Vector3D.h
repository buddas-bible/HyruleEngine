#pragma once
#include <sal.h>

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
		constexpr Vector3D() : e{}
		{}
		constexpr Vector3D(float _x, float _y, float _z) 
			: e{ _x, _y, _z }
		{}
		constexpr Vector3D(const Vector3D&) = default;
		constexpr Vector3D(Vector3D&&) = default;
		constexpr Vector3D(_In_reads_(3) const float* _arr) :
			e{ _arr[0], _arr[1], _arr[2] }
		{}
		~Vector3D() = default;

		constexpr Vector3D& operator= (const Vector3D&) = default;
		constexpr Vector3D& operator= (Vector3D&&) = default;

		explicit operator Matrix1x3();

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

		static constexpr inline Vector3D Zero()
		{
			return Vector3D{};
		}

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		float Length() const;
		float LengthSquare() const;
		Vector3D Cross(const Vector3D&) const;
		float Dot(const Vector3D&) const;
		float ScalarTriple(const Vector3D&, const Vector3D&) const;
		Vector3D VectorTriple(const Vector3D&, const Vector3D&) const;
		float FastInvSqrt(float) const;
		Vector3D& Normalize();				// ���͸� ����ȭ�ϰ� ��ȯ
		Vector3D Normalized() const;		// ����ȭ�� ���ο� ���͸� ��ȯ

		static Vector3D Forward();
		static Vector3D Up();
		static Vector3D Right();

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Vector3D& operator += (const Vector3D&);
		Vector3D& operator -= (const Vector3D&);

		Vector3D operator + (const Vector3D&) const;
		Vector3D operator - (const Vector3D&) const;
		Vector3D operator - () const;

		Vector3D& operator *= (const float);
		Vector3D& operator /= (const float);

		Vector3D operator * (const float) const;
		Vector3D operator / (const float) const;

		Vector3D& operator*= (const Matrix3x3&);
		Vector3D operator* (const Matrix3x3&) const;

		Vector3D& operator*= (const Matrix4x4&);
		Vector3D operator* (const Matrix4x4&) const;

		bool operator == (const Vector3D&) const;

		friend Vector3D operator * (const Quaternion&, const Vector3D&);
	};

	Vector3D operator * (const Quaternion&, const Vector3D&);
}
