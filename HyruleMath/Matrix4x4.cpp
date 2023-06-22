#include "Matrix4x4.h"

namespace Hyrule
{
	Matrix4x4::Matrix4x4(
		float _e00, float _e01, float _e02, float _e03,
		float _e10, float _e11, float _e12, float _e13,
		float _e20, float _e21, float _e22, float _e23,
		float _e30, float _e31, float _e32, float _e33) noexcept
		:
		e{ 
			_e00, _e01, _e02, _e03,
			_e10, _e11, _e12, _e13,
			_e20, _e21, _e22, _e23,
			_e30, _e31, _e32, _e33
		}
	{

	}

	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const noexcept
	{
		return Matrix4x4(
			(this->e[0][0] + other.e[0][0]),
			(this->e[0][1] + other.e[0][1]),
			(this->e[0][2] + other.e[0][2]),
			(this->e[0][3] + other.e[0][3]),

			(this->e[1][0] + other.e[1][0]),
			(this->e[1][1] + other.e[1][1]),
			(this->e[1][2] + other.e[1][2]),
			(this->e[1][3] + other.e[1][3]),

			(this->e[2][0] + other.e[2][0]),
			(this->e[2][1] + other.e[2][1]),
			(this->e[2][2] + other.e[2][2]),
			(this->e[2][3] + other.e[2][3]),

			(this->e[3][0] + other.e[3][0]),
			(this->e[3][1] + other.e[3][1]),
			(this->e[3][2] + other.e[3][2]),
			(this->e[3][3] + other.e[3][3])
		);
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) noexcept
	{
		this->e[0][0] += other.e[0][0];
		this->e[0][1] += other.e[0][1];
		this->e[0][2] += other.e[0][2];
		this->e[0][3] += other.e[0][3];

		this->e[1][0] += other.e[1][0];
		this->e[1][1] += other.e[1][1];
		this->e[1][2] += other.e[1][2];
		this->e[1][3] += other.e[1][3];

		this->e[2][0] += other.e[2][0];
		this->e[2][1] += other.e[2][1];
		this->e[2][2] += other.e[2][2];
		this->e[2][3] += other.e[2][3];

		this->e[3][0] += other.e[3][0];
		this->e[3][1] += other.e[3][1];
		this->e[3][2] += other.e[3][2];
		this->e[3][3] += other.e[3][3];

		return *this;
	}

	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const noexcept
	{
		return Matrix4x4(
			(this->e[0][0] - other.e[0][0]),
			(this->e[0][1] - other.e[0][1]),
			(this->e[0][2] - other.e[0][2]),
			(this->e[0][3] - other.e[0][3]),

			(this->e[1][0] - other.e[1][0]),
			(this->e[1][1] - other.e[1][1]),
			(this->e[1][2] - other.e[1][2]),
			(this->e[1][3] - other.e[1][3]),

			(this->e[2][0] - other.e[2][0]),
			(this->e[2][1] - other.e[2][1]),
			(this->e[2][2] - other.e[2][2]),
			(this->e[2][3] - other.e[2][3]),

			(this->e[3][0] - other.e[3][0]),
			(this->e[3][1] - other.e[3][1]),
			(this->e[3][2] - other.e[3][2]),
			(this->e[3][3] - other.e[3][3])
		);
	}

	Matrix4x4& Matrix4x4::operator-(const Matrix4x4& other) noexcept
	{
		this->e[0][0] -= other.e[0][0];
		this->e[0][1] -= other.e[0][1];
		this->e[0][2] -= other.e[0][2];
		this->e[0][3] -= other.e[0][3];
		
		this->e[1][0] -= other.e[1][0];
		this->e[1][1] -= other.e[1][1];
		this->e[1][2] -= other.e[1][2];
		this->e[1][3] -= other.e[1][3];
		
		this->e[2][0] -= other.e[2][0];
		this->e[2][1] -= other.e[2][1];
		this->e[2][2] -= other.e[2][2];
		this->e[2][3] -= other.e[2][3];
		
		this->e[3][0] -= other.e[3][0];
		this->e[3][1] -= other.e[3][1];
		this->e[3][2] -= other.e[3][2];
		this->e[3][3] -= other.e[3][3];

		return *this;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const noexcept
	{
		return Matrix4x4(
			(this->e[0][0] * other.e[0][0] + this->e[0][1] * other.e[1][0] + this->e[0][2] * other.e[2][0] + this->e[0][3] * other.e[3][0]),
			(this->e[0][0] * other.e[0][1] + this->e[0][1] * other.e[1][1] + this->e[0][2] * other.e[2][1] + this->e[0][3] * other.e[3][1]),
			(this->e[0][0] * other.e[0][2] + this->e[0][1] * other.e[1][2] + this->e[0][2] * other.e[2][2] + this->e[0][3] * other.e[3][2]),
			(this->e[0][0] * other.e[0][3] + this->e[0][1] * other.e[1][3] + this->e[0][2] * other.e[2][3] + this->e[0][3] * other.e[3][3]),

			(this->e[1][0] * other.e[0][0] + this->e[1][1] * other.e[1][0] + this->e[1][2] * other.e[2][0] + this->e[1][3] * other.e[3][0]),
			(this->e[1][0] * other.e[0][1] + this->e[1][1] * other.e[1][1] + this->e[1][2] * other.e[2][1] + this->e[1][3] * other.e[3][1]),
			(this->e[1][0] * other.e[0][2] + this->e[1][1] * other.e[1][2] + this->e[1][2] * other.e[2][2] + this->e[1][3] * other.e[3][2]),
			(this->e[1][0] * other.e[0][3] + this->e[1][1] * other.e[1][3] + this->e[1][2] * other.e[2][3] + this->e[1][3] * other.e[3][3]),

			(this->e[2][0] * other.e[0][0] + this->e[2][1] * other.e[1][0] + this->e[2][2] * other.e[2][0] + this->e[2][3] * other.e[3][0]),
			(this->e[2][0] * other.e[0][1] + this->e[2][1] * other.e[1][1] + this->e[2][2] * other.e[2][1] + this->e[2][3] * other.e[3][1]),
			(this->e[2][0] * other.e[0][2] + this->e[2][1] * other.e[1][2] + this->e[2][2] * other.e[2][2] + this->e[2][3] * other.e[3][2]),
			(this->e[2][0] * other.e[0][3] + this->e[2][1] * other.e[1][3] + this->e[2][2] * other.e[2][3] + this->e[2][3] * other.e[3][3]),

			(this->e[3][0] * other.e[0][0] + this->e[3][1] * other.e[1][0] + this->e[3][2] * other.e[2][0] + this->e[3][3] * other.e[3][0]),
			(this->e[3][0] * other.e[0][1] + this->e[3][1] * other.e[1][1] + this->e[3][2] * other.e[2][1] + this->e[3][3] * other.e[3][1]),
			(this->e[3][0] * other.e[0][2] + this->e[3][1] * other.e[1][2] + this->e[3][2] * other.e[2][2] + this->e[3][3] * other.e[3][2]),
			(this->e[3][0] * other.e[0][3] + this->e[3][1] * other.e[1][3] + this->e[3][2] * other.e[2][3] + this->e[3][3] * other.e[3][3])
		);
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) noexcept
	{
		Matrix4x4 temp = *this;

		this->e00 = temp.e[0][0] * other.e[0][0] + temp.e[0][1] * other.e[1][0] + temp.e[0][2] * other.e[2][0] + temp.e[0][3] * other.e[3][0];
		this->e01 = temp.e[0][0] * other.e[0][1] + temp.e[0][1] * other.e[1][1] + temp.e[0][2] * other.e[2][1] + temp.e[0][3] * other.e[3][1];
		this->e02 = temp.e[0][0] * other.e[0][2] + temp.e[0][1] * other.e[1][2] + temp.e[0][2] * other.e[2][2] + temp.e[0][3] * other.e[3][2];
		this->e03 = temp.e[0][0] * other.e[0][3] + temp.e[0][1] * other.e[1][3] + temp.e[0][2] * other.e[2][3] + temp.e[0][3] * other.e[3][3];
		
		this->e10 = temp.e[1][0] * other.e[0][0] + temp.e[1][1] * other.e[1][0] + temp.e[1][2] * other.e[2][0] + temp.e[1][3] * other.e[3][0];
		this->e11 = temp.e[1][0] * other.e[0][1] + temp.e[1][1] * other.e[1][1] + temp.e[1][2] * other.e[2][1] + temp.e[1][3] * other.e[3][1];
		this->e12 = temp.e[1][0] * other.e[0][2] + temp.e[1][1] * other.e[1][2] + temp.e[1][2] * other.e[2][2] + temp.e[1][3] * other.e[3][2];
		this->e13 = temp.e[1][0] * other.e[0][3] + temp.e[1][1] * other.e[1][3] + temp.e[1][2] * other.e[2][3] + temp.e[1][3] * other.e[3][3];
		
		this->e20 = temp.e[2][0] * other.e[0][0] + temp.e[2][1] * other.e[1][0] + temp.e[2][2] * other.e[2][0] + temp.e[2][3] * other.e[3][0];
		this->e21 = temp.e[2][0] * other.e[0][1] + temp.e[2][1] * other.e[1][1] + temp.e[2][2] * other.e[2][1] + temp.e[2][3] * other.e[3][1];
		this->e22 = temp.e[2][0] * other.e[0][2] + temp.e[2][1] * other.e[1][2] + temp.e[2][2] * other.e[2][2] + temp.e[2][3] * other.e[3][2];
		this->e23 = temp.e[2][0] * other.e[0][3] + temp.e[2][1] * other.e[1][3] + temp.e[2][2] * other.e[2][3] + temp.e[2][3] * other.e[3][3];
		
		this->e30 = temp.e[3][0] * other.e[0][0] + temp.e[3][1] * other.e[1][0] + temp.e[3][2] * other.e[2][0] + temp.e[3][3] * other.e[3][0];
		this->e31 = temp.e[3][0] * other.e[0][1] + temp.e[3][1] * other.e[1][1] + temp.e[3][2] * other.e[2][1] + temp.e[3][3] * other.e[3][1];
		this->e32 = temp.e[3][0] * other.e[0][2] + temp.e[3][1] * other.e[1][2] + temp.e[3][2] * other.e[2][2] + temp.e[3][3] * other.e[3][2];
		this->e33 = temp.e[3][0] * other.e[0][3] + temp.e[3][1] * other.e[1][3] + temp.e[3][2] * other.e[2][3] + temp.e[3][3] * other.e[3][3];

		return *this;
	}
}