#pragma once
// #include <emmintrin.h>
#include <smmintrin.h>

namespace Hyrule
{
	struct Vector4D;

	struct Quaternion
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Quaternion() :
			m{}
		{}
		constexpr Quaternion(float _w, float _x, float _y, float _z) :
			x(_x), y(_y), z(_z), w(_w)
		{}
		constexpr Quaternion(const Quaternion&) = default;
		constexpr Quaternion(Quaternion&&) = default;
		~Quaternion() = default;

		constexpr Quaternion& operator= (const Quaternion&) = default;
		constexpr Quaternion& operator= (Quaternion&&) = default;

		explicit operator Vector4D();

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

		static inline Quaternion Identity()
		{
			return Quaternion{ 1.f, 0.f, 0.f, 0.f };
		}

		/// <summary>
		/// ���ʹϾ� �Լ�
		/// </summary>
		float Length() const;
		float LengthSquare() const;
		float FastInvSqrt(float) const;
		float Dot(const Quaternion&) const;

		Quaternion Conjugate() const;
		Quaternion Inverse() const;
		Quaternion& Normalize();
		Quaternion Normalized() const;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Quaternion& operator += (const Quaternion&);
		Quaternion& operator -= (const Quaternion&);

		Quaternion operator + (const Quaternion&) const;
		Quaternion operator - (const Quaternion&) const;
		Quaternion operator - () const;

		Quaternion& operator *= (const Quaternion&);
		Quaternion& operator /= (const Quaternion&);

		Quaternion operator * (const Quaternion&) const;
		Quaternion operator / (const Quaternion&) const;

		Quaternion& operator *= (const float);
		Quaternion& operator /= (const float);

		Quaternion operator * (const float) const;
		Quaternion operator / (const float) const;

		friend Quaternion operator *= (const float, const Quaternion&);
		friend Quaternion operator /= (const float, const Quaternion&);

		friend Quaternion operator * (const float, const Quaternion&);
		friend Quaternion operator / (const float, const Quaternion&);

		bool operator == (const Quaternion&) const;
	};

	Quaternion operator *= (const float, const Quaternion&);
	Quaternion operator /= (const float, const Quaternion&);
	Quaternion operator * (const float, const Quaternion&);
	Quaternion operator / (const float, const Quaternion&);
}

