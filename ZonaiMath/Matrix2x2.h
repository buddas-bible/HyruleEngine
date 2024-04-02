#pragma once
#include "Matrix1x2.h"

namespace ZonaiMath
{
	class Vector2D;
	class Matrix1x2;

	class Matrix2x2
	{
	public:
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Matrix2x2() :
			e{}
		{}
		constexpr Matrix2x2(
			float _e00, float _e01,
			float _e10, float _e11) :
			e
			{
				_e00, _e01,
				_e10, _e11
			}
		{}
		constexpr Matrix2x2(
			const Matrix1x2& _m1,
			const Matrix1x2& _m2) :
			r{ _m1, _m2 }
		{}
		constexpr Matrix2x2(const Matrix2x2&) = default;
		constexpr Matrix2x2(Matrix2x2&&) = default;
		~Matrix2x2() = default;

		constexpr Matrix2x2& operator = (const Matrix2x2&) = default;
		constexpr Matrix2x2& operator = (Matrix2x2&&) = default;

		union
		{
			struct
			{
				float
					e00, e01,
					e10, e11;
			};
			float e[2][2];
			Matrix1x2 r[2];
		};

		/// <summary>
		/// ���� ����
		/// </summary>
		static const Matrix2x2 Zero;
		static const Matrix2x2 Identity;

		/// <summary>
		/// ��� �Լ�
		/// </summary>
		float Determinant() const;
		Matrix2x2 Transpose() const;
		Matrix2x2 Inverse() const;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Matrix2x2 operator+ (const Matrix2x2&) const;
		Matrix2x2& operator+= (const Matrix2x2&);
		Matrix2x2 operator- (const Matrix2x2&) const;
		Matrix2x2& operator-= (const Matrix2x2&);
		Matrix2x2 operator* (const Matrix2x2&) const;
		Matrix2x2& operator*= (const Matrix2x2&);

		bool operator == (const Matrix2x2&);
	};

	const Matrix2x2 Matrix2x2::Zero = {};
	const Matrix2x2 Matrix2x2::Identity = {
				1.f, 0.f,
				0.f, 1.f,
	};
}
