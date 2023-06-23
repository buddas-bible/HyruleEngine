#pragma once

namespace Hyrule
{
	struct Vector3D;

	struct Matrix3x3
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		Matrix3x3() noexcept = default;
		Matrix3x3(
			float _e00, float _e01, float _e02,
			float _e10, float _e11, float _e12,
			float _e20, float _e21, float _e22) noexcept;
		Matrix3x3(const Matrix3x3&) noexcept = default;
		Matrix3x3(Matrix3x3&&) noexcept = default;
		~Matrix3x3() noexcept = default;

		Matrix3x3& operator= (const Matrix3x3&) noexcept = default;
		Matrix3x3& operator= (Matrix3x3&&) noexcept = default;

		/// <summary>
		/// 멤버 변수
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
		/// 전역 함수
		/// </summary>
		static inline Matrix3x3 Identity() noexcept;

		/// <summary>
		/// 멤버 함수
		/// </summary>
		float Determinant() noexcept;
		Matrix3x3 Transpose() noexcept;
		Matrix3x3 Inverse() noexcept;

		/// <summary>
		/// 연산자 오버로딩
		/// </summary>
		Matrix3x3 operator+ (const Matrix3x3&) const noexcept;
		Matrix3x3& operator+= (const Matrix3x3&) noexcept;
		Matrix3x3 operator- (const Matrix3x3&) const noexcept;
		Matrix3x3& operator-= (const Matrix3x3&) noexcept;
		Matrix3x3 operator* (const Matrix3x3&) const noexcept;
		Matrix3x3& operator*= (const Matrix3x3&) noexcept;
		Matrix3x3 operator/ (const Matrix3x3&) const noexcept;
		Matrix3x3& operator/= (const Matrix3x3&) noexcept;
	};

	// Matrix3x3 AxisAndAngleRotation(const Vector3D& vec, float angle);
}