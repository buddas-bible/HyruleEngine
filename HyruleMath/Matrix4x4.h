#pragma once
#include "Matrix1x4.h"
#include "Vector4D.h"

namespace Hyrule
{
	struct Matrix1x4;
	struct Quaternion;

	struct Matrix4x4
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		constexpr Matrix4x4() noexcept;
		constexpr Matrix4x4(
			float, float, float, float,
			float, float, float, float,
			float, float, float, float,
			float, float, float, float
		) noexcept;
		constexpr Matrix4x4(
			const Matrix1x4&,
			const Matrix1x4&,
			const Matrix1x4&,
			const Matrix1x4&
		) noexcept;
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
		/// 전역 함수
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
		
		/// <summary>
		/// 멤버 함수
		/// </summary>
		float Determinant() noexcept;
		float Determinant3x3() noexcept;
		Matrix4x4 Transpose() noexcept;
		Matrix4x4 Inverse() noexcept;

		/// <summary>
		/// 연산자 오버로딩
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