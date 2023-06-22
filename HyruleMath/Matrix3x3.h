#pragma once

namespace Hyrule
{
	class Vector3D;

	struct Matrix3x3
	{
		/// <summary>
		/// Ư�� ��� �Լ�
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
		/// ��� �Լ�
		/// </summary>
// 		static Matrix3x3 IdentityMatrix();
// 		static Matrix3x3 TransformMatrix(								// ��ȯ���
// 			float moveX, float moveY,
// 			float theta, float scaleX,
// 			float scaleY);
// 
// 
// 		static Matrix3x3 TranslateMatrix(float moveX, float moveY);		// �̵� ��ȯ ���
// 		static Matrix3x3 RotateMatrix(float theta);						// ȸ�� ��ȯ ���
// 		static Matrix3x3 ScaleMatrix(float scaleX, float scaleY);		// ��ô ��ȯ ���
// 		static Matrix3x3 ScaleRotate(float scaleX, float scaleY, float theta);

		float Determinant();

		/// <summary>
		/// ������ �����ε�
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

	Matrix3x3 AxisAndAngleRotation(const Vector3D& vec, float angle);
}