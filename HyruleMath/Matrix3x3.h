#pragma once

namespace Hyrule
{
	class Vector3D;

	struct Matrix3x3
	{
		Matrix3x3() noexcept = default;
		Matrix3x3(
			float e00, float e01, float e02,
			float e10, float e11, float e12,
			float e20, float e21, float e22) noexcept;
		Matrix3x3(const Matrix3x3& mat) noexcept = default;
		Matrix3x3(const Matrix3x3&& mat) noexcept = default;
		~Matrix3x3() noexcept = default;

		union
		{
			struct
			{
				float _e0, _e1, _e2, _e3, _e4, _e5, _e6, _e7, _e8;
			};
			float e[3][3];
		};

		static Matrix3x3 IdentityMatrix();
		static Matrix3x3 TransformMatrix(								// ��ȯ���
			float moveX, float moveY,
			float theta, float scaleX,
			float scaleY);

		static Matrix3x3 TranslateMatrix(float moveX, float moveY);		// �̵� ��ȯ ���
		static Matrix3x3 RotateMatrix(float theta);						// ȸ�� ��ȯ ���
		static Matrix3x3 ScaleMatrix(float scaleX, float scaleY);		// ��ô ��ȯ ���
		static Matrix3x3 ScaleRotate(float scaleX, float scaleY, float theta);

		Matrix3x3 operator + (const Matrix3x3& other) const;
		Matrix3x3 operator - (const Matrix3x3& other) const;
		Matrix3x3 operator * (const Matrix3x3& other) const;
		Matrix3x3 operator = (const Matrix3x3& other) noexcept;
		Matrix3x3 operator = (const Matrix3x3&& other) noexcept;
	};

	Matrix3x3 AxisAndAngleRotation(const Vector3D& vec, float angle);
}