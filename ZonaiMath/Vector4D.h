#pragma once
#include <smmintrin.h>
#include <sal.h>

namespace ZonaiMath
{
	class Vector3D;
	class Matrix1x4;
	class Matrix4x4;
	class Quaternion;

	class Vector4D
	{
	public:
		/// <summary>
			/// Ư�� ��� �Լ�
			/// </summary>
		constexpr Vector4D() :
			e{}
		{}
		constexpr Vector4D(__m128 _m) :
			m{ _m }
		{}
		constexpr Vector4D(float _a) :
			e{ _a, _a, _a, _a }
		{}
		constexpr Vector4D(float _x, float _y, float _z, float _w) :
			e{ _x, _y, _z, _w }
		{}
		constexpr Vector4D(const Vector4D& other) = default;
		constexpr Vector4D(Vector4D&& other) = default;
		constexpr Vector4D(_In_reads_(4) const float* _arr) :
			e{ _arr[0], _arr[1], _arr[2], _arr[3] }
		{}
		Vector4D(const Vector3D&, const float);
		~Vector4D() = default;

		constexpr Vector4D& operator= (const Vector4D&) = default;
		constexpr Vector4D& operator= (Vector4D&&) = default;

		explicit operator Matrix1x4();
		explicit operator Quaternion();

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float e[4];
			__m128 m;
		};

		static const Vector4D Zero;

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		float Length() const;
		float LengthSquare() const;
		Vector4D Cross(const Vector4D&) const;
		float Dot(const Vector4D&) const;
		float FastInvSqrt(float) const;			// ��� �� �Լ��� ���⿡ ������� �� ������..
		Vector4D& Normalize();
		Vector4D Normalized() const;

		// Vector3D ������� ó���ϰ� ���� ��
		float Dot3(const Vector4D&) const;
		Vector4D& Normalize3();
		Vector4D Normalized3() const;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Vector4D& operator += (const Vector4D&);
		Vector4D& operator -= (const Vector4D&);

		Vector4D operator + (const Vector4D&) const;
		Vector4D operator - (const Vector4D&) const;
		Vector4D operator - () const;

		Vector4D& operator *= (const float);
		Vector4D& operator /= (const float);

		Vector4D operator * (const float) const;
		Vector4D operator / (const float) const;

		Vector4D& operator *= (const Matrix4x4&);
		Vector4D operator * (const Matrix4x4&) const;

		bool operator == (const Vector4D&) const;
	};
	
	const Vector4D Vector4D::Zero = {};
}

