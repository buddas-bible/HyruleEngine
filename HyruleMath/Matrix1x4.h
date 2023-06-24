#pragma once

namespace Hyrule
{
	struct Vector4D;

	struct Matrix1x4
	{
		/// <summary>
		/// Æ¯¼ö ¸â¹ö ÇÔ¼ö
		/// </summary>
		Matrix1x4() noexcept = default;
		Matrix1x4(
			float, float, float, float) noexcept;
		Matrix1x4(const Matrix1x4&) noexcept = default;
		Matrix1x4(Matrix1x4&&) noexcept = default;
		~Matrix1x4() noexcept = default;

		Matrix1x4& operator= (const Matrix1x4&) noexcept = default;
		Matrix1x4& operator= (Matrix1x4&&) noexcept = default;

		explicit operator Vector4D() noexcept;

		/// <summary>
		/// ¸â¹ö º¯¼ö
		/// </summary>
		union
		{
			struct  
			{
				float e00, e01, e02, e03;
			};
			float e[4];
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

