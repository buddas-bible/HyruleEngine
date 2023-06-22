#pragma once

namespace Hyrule
{
	struct Matrix4x4
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		Matrix4x4() noexcept = default;
		Matrix4x4(
			float e00, float e01, float e02, float e03,
			float e10, float e11, float e12, float e13,
			float e20, float e21, float e22, float e23,
			float e30, float e31, float e32, float e33
		) noexcept;
		// Matrix4x4(const Matrix3x3& mat) noexcept;
		Matrix4x4(const Matrix4x4& mat) noexcept = default;
		Matrix4x4(Matrix4x4&& mat) noexcept = default;
		~Matrix4x4() noexcept = default;

		Matrix4x4& operator = (const Matrix4x4& other) noexcept = default;
		Matrix4x4& operator = (Matrix4x4&& other) noexcept = default;

		union
		{
			struct
			{
				float e00, e01, e02, e03, e10, e11, e12, e13, e20, e21, e22, e23, e30, e31, e32, e33;
			};
			float e[4][4];
		};

		/// <summary>
		/// 
		/// </summary>
		// static Matrix4x4&& IdentityMatrix();
		// 
		// static Matrix4x4 TransformMatrix(											// ��ȯ���
		// 	float moveX, float moveY, float moveZ,
		// 	float thetaX, float thetaY, float thetaZ,
		// 	float scaleX, float scaleY, float scaleZ);
		// static Matrix4x4 TranslateMatrix(float moveX, float moveY, float moveZ);	// �̵� ��ȯ ���
		// static Matrix4x4 RotateMatrix(float thetaX, float thetaY, float thetaZ);	// ȸ�� ��ȯ ���
		// // static Matrix4x4 RotateMatrix(const Quaternion& q);	// ȸ�� ��ȯ ���
		// static Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ);		// ��ô ��ȯ ���
		// static Matrix4x4 ScaleRotate(
		// 	float scaleX, float scaleY, float scaleZ,
		// 	float thetaX, float thetaY, float thetaZ);

		/// <summary>
		/// ������ �����ε�
		/// </summary>
		Matrix4x4 operator+ (const Matrix4x4& other) const noexcept;
		Matrix4x4& operator+= (const Matrix4x4& other) noexcept;
		Matrix4x4 operator- (const Matrix4x4& other) const noexcept;
		Matrix4x4& operator- (const Matrix4x4& other) noexcept;
		Matrix4x4 operator* (const Matrix4x4& other) const noexcept;
		Matrix4x4& operator*= (const Matrix4x4& other) noexcept;
		Matrix4x4 operator/ (const Matrix4x4& other) const noexcept;
		Matrix4x4& operator/= (const Matrix4x4& other) noexcept;
	};
}