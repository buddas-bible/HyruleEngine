#include "Matrix3x3.h"

namespace Hyrule
{

	Matrix3x3::Matrix3x3(
		float _e00, float _e01, float _e02, 
		float _e10, float _e11, float _e12, 
		float _e20, float _e21, float _e22) noexcept
		:
		e
		{
			_e00, _e01, _e02, 
			_e10, _e11, _e12, 
			_e20, _e21, _e22
		}
	{

	}

	Matrix3x3 Matrix3x3::Transpose() noexcept
	{
		return Matrix3x3
		{
			e00, e10, e20,
			e01, e11, e21,
			e02, e12, e22
		};
	}

	Matrix3x3 Matrix3x3::Inverse() noexcept
	{
		Matrix3x3 result{};

		float det = Determinant();

		if (det == 0.0f)
		{
			// ��Ľ��� 0�� ��쿣 ������� �������� ����.
			return result;
		}

		float invDet = 1.0f / det;

		result.e00 = (e11 * e22 - e21 * e12) * invDet;
		result.e01 = (e02 * e21 - e01 * e22) * invDet;
		result.e02 = (e01 * e12 - e02 * e11) * invDet;
		result.e10 = (e12 * e20 - e10 * e22) * invDet;
		result.e11 = (e00 * e22 - e02 * e20) * invDet;
		result.e12 = (e02 * e10 - e00 * e12) * invDet;
		result.e20 = (e10 * e21 - e11 * e20) * invDet;
		result.e21 = (e01 * e20 - e00 * e21) * invDet;
		result.e22 = (e00 * e11 - e01 * e10) * invDet;

		return result;
	}

	Matrix3x3 Matrix3x3::Identity() noexcept
	{
		return Matrix3x3
		{
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 1.f,
		};
	}

	float Matrix3x3::Determinant() noexcept
	{
		float det = 
			e00 * (e11 * e22 - e21 * e12) - 
			e01 * (e10 * e22 - e20 * e12) + 
			e02 * (e10 * e21 - e20 * e11);

		return det;
	}

	Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const noexcept
	{
		return Matrix3x3
		(
			(this->e[0][0] + other.e[0][0]),
			(this->e[0][1] + other.e[0][1]),
			(this->e[0][2] + other.e[0][2]),

			(this->e[1][0] + other.e[1][0]),
			(this->e[1][1] + other.e[1][1]),
			(this->e[1][2] + other.e[1][2]),

			(this->e[2][0] + other.e[2][0]),
			(this->e[2][1] + other.e[2][1]),
			(this->e[2][2] + other.e[2][2])
		);
	}

	Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) noexcept
	{
		this->e00 += other.e00;
		this->e01 += other.e01;
		this->e02 += other.e02;

		this->e10 += other.e10;
		this->e11 += other.e11;
		this->e12 += other.e12;

		this->e20 += other.e20;
		this->e21 += other.e21;
		this->e22 += other.e22;

		return *this;
	}

	Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const noexcept
	{
		return Matrix3x3
		(
			(this->e[0][0] - other.e[0][0]),
			(this->e[0][1] - other.e[0][1]),
			(this->e[0][2] - other.e[0][2]),

			(this->e[1][0] - other.e[1][0]),
			(this->e[1][1] - other.e[1][1]),
			(this->e[1][2] - other.e[1][2]),

			(this->e[2][0] - other.e[2][0]),
			(this->e[2][1] - other.e[2][1]),
			(this->e[2][2] - other.e[2][2])
		);
	}

	Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) noexcept
	{
		this->e00 -= other.e00;
		this->e01 -= other.e01;
		this->e02 -= other.e02;

		this->e10 -= other.e10;
		this->e11 -= other.e11;
		this->e12 -= other.e12;

		this->e20 -= other.e20;
		this->e21 -= other.e21;
		this->e22 -= other.e22;

		return *this;
	}

	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const noexcept
	{
		return Matrix3x3
		(
			(this->e[0][0] * other.e[0][0] + this->e[0][1] * other.e[1][0] + this->e[0][2] * other.e[2][0]),
			(this->e[0][0] * other.e[0][1] + this->e[0][1] * other.e[1][1] + this->e[0][2] * other.e[2][1]),
			(this->e[0][0] * other.e[0][2] + this->e[0][1] * other.e[1][2] + this->e[0][2] * other.e[2][2]),

			(this->e[1][0] * other.e[0][0] + this->e[1][1] * other.e[1][0] + this->e[1][2] * other.e[2][0]),
			(this->e[1][0] * other.e[0][1] + this->e[1][1] * other.e[1][1] + this->e[1][2] * other.e[2][1]),
			(this->e[1][0] * other.e[0][2] + this->e[1][1] * other.e[1][2] + this->e[1][2] * other.e[2][2]),

			(this->e[2][0] * other.e[0][0] + this->e[2][1] * other.e[1][0] + this->e[2][2] * other.e[2][0]),
			(this->e[2][0] * other.e[0][1] + this->e[2][1] * other.e[1][1] + this->e[2][2] * other.e[2][1]),
			(this->e[2][0] * other.e[0][2] + this->e[2][1] * other.e[1][2] + this->e[2][2] * other.e[2][2])
		);
	}

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& other) noexcept
	{
		(this->e[0][0] * other.e[0][0] + this->e[0][1] * other.e[1][0] + this->e[0][2] * other.e[2][0]);
		(this->e[0][0] * other.e[0][1] + this->e[0][1] * other.e[1][1] + this->e[0][2] * other.e[2][1]);
		(this->e[0][0] * other.e[0][2] + this->e[0][1] * other.e[1][2] + this->e[0][2] * other.e[2][2]);

		(this->e[1][0] * other.e[0][0] + this->e[1][1] * other.e[1][0] + this->e[1][2] * other.e[2][0]);
		(this->e[1][0] * other.e[0][1] + this->e[1][1] * other.e[1][1] + this->e[1][2] * other.e[2][1]);
		(this->e[1][0] * other.e[0][2] + this->e[1][1] * other.e[1][2] + this->e[1][2] * other.e[2][2]);

		(this->e[2][0] * other.e[0][0] + this->e[2][1] * other.e[1][0] + this->e[2][2] * other.e[2][0]);
		(this->e[2][0] * other.e[0][1] + this->e[2][1] * other.e[1][1] + this->e[2][2] * other.e[2][1]);
		(this->e[2][0] * other.e[0][2] + this->e[2][1] * other.e[1][2] + this->e[2][2] * other.e[2][2]);

		return *this;
	}

}
