#include "Matrix3x3.h"

namespace Hyrule
{

	Matrix3x3::Matrix3x3(
		float _e00, float _e01, float _e02, 
		float _e10, float _e11, float _e12, 
		float _e20, float _e21, float _e22) noexcept
		:
		e{
			_e00, _e01, _e02, 
			_e10, _e11, _e12, 
			_e20, _e21, _e22
		}
	{

	}

	float Matrix3x3::Determinant()
	{
		float a11 = -1.f;
		float a12 = 1.f;
		float a13 = -1.f;
		float a14 = 1.f;

		float a21 = -1.f;
		float a22 = -1.f;
		float a23 = -1.f;
		float a24 = -1.f;
		
		float a31 = -1.f;
		float a32 = -1.f;
		float a33 = -1.f;
		float a34 = -1.f;
		
		float a41 = -1.f;
		float a42 = -1.f;
		float a43 = -1.f;
		float a44 = -1.f;


		return 10;
	}

	Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const noexcept
	{
		return Matrix3x3(
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

	Matrix3x3& Matrix3x3::operator+=(const Matrix3x3&) noexcept
	{
		return *this;
	}

	Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const noexcept
	{
		return Matrix3x3(
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

	Matrix3x3& Matrix3x3::operator-=(const Matrix3x3&) noexcept
	{
		return *this;
	}

	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const noexcept
	{
		return Matrix3x3(
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

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3&) noexcept
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
