#pragma once

namespace Hyrule
{
	struct Vector3D;

	struct Matrix1x3
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		Matrix1x3() noexcept = default;
		Matrix1x3(
			float, float, float) noexcept;
		Matrix1x3(const Matrix1x3&) noexcept = default;
		Matrix1x3(Matrix1x3&&) noexcept = default;
		~Matrix1x3() noexcept = default;

		Matrix1x3& operator= (const Matrix1x3&) noexcept = default;
		Matrix1x3& operator= (Matrix1x3&&) noexcept = default;

		explicit operator Vector3D() noexcept;

		/// <summary>
		/// ��� ����
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