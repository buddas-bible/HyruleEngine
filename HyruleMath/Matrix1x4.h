#pragma once
#include <emmintrin.h>

namespace Hyrule
{
	struct Vector4D;

	struct Matrix1x4
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Matrix1x4() noexcept;
		constexpr Matrix1x4(
			float, float, float, float) noexcept;
		constexpr Matrix1x4(const Matrix1x4&) noexcept = default;
		constexpr Matrix1x4(Matrix1x4&&) noexcept = default;
		~Matrix1x4() noexcept = default;

		constexpr Matrix1x4& operator= (const Matrix1x4&) noexcept = default;
		constexpr Matrix1x4& operator= (Matrix1x4&&) noexcept = default;

		constexpr explicit operator Vector4D() noexcept;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct  
			{
				float e00, e01, e02, e03;
			};
			float e[4];
			__m128 m;
		};

		Matrix1x4& operator += (const Matrix1x4&) noexcept;
		Matrix1x4& operator -= (const Matrix1x4&) noexcept;

		Matrix1x4 operator + (const Matrix1x4&) const noexcept;
		Matrix1x4 operator - (const Matrix1x4&) const noexcept;
		Matrix1x4 operator - () const noexcept;

		Matrix1x4& operator *= (const float) noexcept;
		Matrix1x4& operator /= (const float) noexcept;

		Matrix1x4 operator * (const float) const noexcept;
		Matrix1x4 operator / (const float) const noexcept;
	};
}
