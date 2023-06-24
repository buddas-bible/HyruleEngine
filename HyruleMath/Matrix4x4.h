#pragma once

namespace Hyrule
{
	class Quaternion;

	struct Matrix4x4
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		Matrix4x4() noexcept = default;
		Matrix4x4(
			float, float, float, float,
			float, float, float, float,
			float, float, float, float,
			float, float, float, float
		) noexcept;
		Matrix4x4(const Matrix4x4&) noexcept = default;
		Matrix4x4(Matrix4x4&&) noexcept = default;
		~Matrix4x4() noexcept = default;

		Matrix4x4& operator = (const Matrix4x4&) noexcept = default;
		Matrix4x4& operator = (Matrix4x4&&) noexcept = default;

		union
		{
			struct
			{
				float e00, e01, e02, e03, e10, e11, e12, e13, e20, e21, e22, e23, e30, e31, e32, e33;
			};
			float e[4][4];
		};

		/// <summary>
		/// ���� �Լ�
		/// </summary>
		static inline Matrix4x4 Identity() noexcept;
		
		/// <summary>
		/// ��� �Լ�
		/// </summary>
		float Determinant() noexcept;
		float Determinant3x3() noexcept;
		Matrix4x4 Transpose() noexcept;
		Matrix4x4 Inverse() noexcept;

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