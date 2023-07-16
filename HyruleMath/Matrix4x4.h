#pragma once
#include <smmintrin.h>

#include "Matrix1x4.h"

namespace Hyrule
{
	struct Matrix1x4;
	struct Quaternion;

	struct Matrix4x4
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Matrix4x4() noexcept :
			m()
		{}
		constexpr Matrix4x4(
			float _e00, float _e01, float _e02, float _e03,
			float _e10, float _e11, float _e12, float _e13,
			float _e20, float _e21, float _e22, float _e23,
			float _e30, float _e31, float _e32, float _e33) noexcept :
			e
			{
				_e00, _e01, _e02, _e03,
				_e10, _e11, _e12, _e13,
				_e20, _e21, _e22, _e23,
				_e30, _e31, _e32, _e33
			}
		{}
		constexpr Matrix4x4(
			__m128 _m0,
			__m128 _m1,
			__m128 _m2,
			__m128 _m3
		) noexcept :
			m { _m0, _m1, _m2, _m3 }
		{}
		constexpr Matrix4x4(
			const Matrix1x4& _m1,
			const Matrix1x4& _m2,
			const Matrix1x4& _m3,
			const Matrix1x4& _m4) noexcept :
			m { _m1, _m2, _m3, _m4 }
		{}
		constexpr Matrix4x4(const Matrix4x4&) noexcept = default;
		constexpr Matrix4x4(Matrix4x4&&) noexcept = default;
		~Matrix4x4() noexcept = default;

		constexpr Matrix4x4& operator = (const Matrix4x4&) noexcept = default;
		constexpr Matrix4x4& operator = (Matrix4x4&&) noexcept = default;

		union
		{
			struct
			{
				float e00, e01, e02, e03, e10, e11, e12, e13, e20, e21, e22, e23, e30, e31, e32, e33;
			};
			float e[4][4];
			Matrix1x4 m[4];
		};

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		static inline Matrix4x4 Identity() noexcept
		{
			return Matrix4x4
			{
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f,
			};
		}

		static inline Matrix4x4 Zero() noexcept
		{
			return Matrix4x4{};
		}
		
		/// <summary>
		/// ��� �Լ�
		/// </summary>
		float Determinant() const noexcept;
		float Determinant3x3() const noexcept;
		Matrix4x4 Transpose() const noexcept;
		Matrix4x4 Inverse() const noexcept;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Matrix4x4 operator+ (const Matrix4x4&) const noexcept;
		Matrix4x4& operator+= (const Matrix4x4&) noexcept;
		Matrix4x4 operator- (const Matrix4x4&) const noexcept;
		Matrix4x4& operator-= (const Matrix4x4&) noexcept;
		Matrix4x4 operator* (const Matrix4x4&) const noexcept;
		Matrix4x4& operator*= (const Matrix4x4&) noexcept;
		// Matrix4x4 operator/ (const Matrix4x4&) const noexcept;
		// Matrix4x4& operator/= (const Matrix4x4&) noexcept;
	};
}