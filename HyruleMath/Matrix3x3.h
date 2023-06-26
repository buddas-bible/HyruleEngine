#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Matrix1x3;

	struct Matrix3x3
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		constexpr Matrix3x3() noexcept;
		constexpr Matrix3x3(
			float, float, float,
			float, float, float,
			float, float, float) noexcept;
		constexpr Matrix3x3(
			const Matrix1x3&,
			const Matrix1x3&,
			const Matrix1x3&
		) noexcept;
		constexpr Matrix3x3(const Matrix3x3&) noexcept = default;
		constexpr Matrix3x3(Matrix3x3&&) noexcept = default;
		~Matrix3x3() noexcept = default;

		constexpr Matrix3x3& operator= (const Matrix3x3&) noexcept = default;
		constexpr Matrix3x3& operator= (Matrix3x3&&) noexcept = default;

		/// <summary>
		/// ��� ����
		/// </summary>
		union
		{
			struct
			{
				float e00, e01, e02, e10, e11, e12, e20, e21, e22;
			};
			float e[3][3];
		};

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		static inline Matrix3x3 Identity() noexcept
		{
			return Matrix3x3
			{
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				0.f, 0.f, 1.f,
			};
		}

		/// <summary>
		/// ��� �Լ�
		/// </summary>
		float Determinant() noexcept;
		Matrix3x3 Transpose() noexcept;
		Matrix3x3 Inverse() noexcept;

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Matrix3x3 operator+ (const Matrix3x3&) const noexcept;
		Matrix3x3& operator+= (const Matrix3x3&) noexcept;
		Matrix3x3 operator- (const Matrix3x3&) const noexcept;
		Matrix3x3& operator-= (const Matrix3x3&) noexcept;
		Matrix3x3 operator* (const Matrix3x3&) const noexcept;
		Matrix3x3& operator*= (const Matrix3x3&) noexcept;
		// Matrix3x3 operator/ (const Matrix3x3&) const noexcept;
		// Matrix3x3& operator/= (const Matrix3x3&) noexcept;
	};
}