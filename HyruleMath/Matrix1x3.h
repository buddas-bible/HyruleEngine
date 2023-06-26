#pragma once

namespace Hyrule
{
	struct Vector3D;

	struct Matrix1x3
	{
		/// <summary>
		/// Æ¯¼ö ¸â¹ö ÇÔ¼ö
		/// </summary>
		constexpr Matrix1x3() noexcept;
		constexpr Matrix1x3(
			float, float, float) noexcept;
		constexpr Matrix1x3(const Matrix1x3&) noexcept = default;
		constexpr Matrix1x3(Matrix1x3&&) noexcept = default;
		~Matrix1x3() noexcept = default;

		constexpr Matrix1x3& operator= (const Matrix1x3&) noexcept = default;
		constexpr Matrix1x3& operator= (Matrix1x3&&) noexcept = default;

		constexpr explicit operator Vector3D() noexcept;

		/// <summary>
		/// ¸â¹ö º¯¼ö
		/// </summary>
		union
		{
			struct
			{
				float e00, e01, e02;
			};
			float e[3];
		};

		Matrix1x3& operator += (const Matrix1x3&) noexcept;
		Matrix1x3& operator -= (const Matrix1x3&) noexcept;

		Matrix1x3 operator + (const Matrix1x3&) const noexcept;
		Matrix1x3 operator - (const Matrix1x3&) const noexcept;
		Matrix1x3 operator - () const noexcept;

		Matrix1x3& operator *= (const float) noexcept;
		Matrix1x3& operator /= (const float) noexcept;

		Matrix1x3 operator * (const float) const noexcept;
		Matrix1x3 operator / (const float) const noexcept;
	};
}