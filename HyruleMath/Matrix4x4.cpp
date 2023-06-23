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

	Matrix4x4 Matrix4x4::Transpose()
	{
		return Matrix4x4
		{
			e00, e10, e20, e30,
			e01, e11, e21, e31,
			e02, e12, e22, e32,
			e03, e13, e23, e33
		};
	}


	Matrix4x4 Matrix4x4::Inverse()
	{
		Matrix4x4 result{};

		float det = Determinant();

		if (det == 0.0f)
		{
			// Matrix is not invertible
			// Handle the error or exception accordingly
			return result;
		}

		float invDet = 1.0f / det;

		result.e00 = (e12 * e23 * e31 - e13 * e22 * e31 + e13 * e21 * e32 - e11 * e23 * e32 - e12 * e21 * e33 + e11 * e22 * e33) * invDet;
		result.e01 = (e03 * e22 * e31 - e02 * e23 * e31 - e03 * e21 * e32 + e01 * e23 * e32 + e02 * e21 * e33 - e01 * e22 * e33) * invDet;
		result.e02 = (e02 * e13 * e31 - e03 * e12 * e31 + e03 * e11 * e32 - e01 * e13 * e32 - e02 * e11 * e33 + e01 * e12 * e33) * invDet;
		result.e03 = (e03 * e12 * e21 - e02 * e13 * e21 - e03 * e11 * e22 + e01 * e13 * e22 + e02 * e11 * e23 - e01 * e12 * e23) * invDet;
		result.e10 = (e13 * e22 * e30 - e12 * e23 * e30 - e13 * e20 * e32 + e10 * e23 * e32 + e12 * e20 * e33 - e10 * e22 * e33) * invDet;
		result.e11 = (e02 * e23 * e30 - e03 * e22 * e30 + e03 * e20 * e32 - e00 * e23 * e32 - e02 * e20 * e33 + e00 * e22 * e33) * invDet;
		result.e12 = (e03 * e12 * e30 - e02 * e13 * e30 - e03 * e10 * e32 + e00 * e13 * e32 + e02 * e10 * e33 - e00 * e12 * e33) * invDet;
		result.e13 = (e02 * e13 * e20 - e03 * e12 * e20 + e03 * e10 * e22 - e00 * e13 * e22 - e02 * e10 * e23 + e00 * e12 * e23) * invDet;
		result.e20 = (e11 * e23 * e30 - e13 * e21 * e30 + e13 * e20 * e31 - e10 * e23 * e31 - e11 * e20 * e33 + e10 * e21 * e33) * invDet;
		result.e21 = (e03 * e21 * e30 - e01 * e23 * e30 - e03 * e20 * e31 + e00 * e23 * e31 + e01 * e20 * e33 - e00 * e21 * e33) * invDet;
		result.e22 = (e01 * e13 * e30 - e03 * e11 * e30 + e03 * e10 * e31 - e00 * e13 * e31 - e01 * e10 * e33 + e00 * e11 * e33) * invDet;
		result.e23 = (e03 * e11 * e20 - e01 * e13 * e20 - e03 * e10 * e21 + e00 * e13 * e21 + e01 * e10 * e23 - e00 * e11 * e23) * invDet;
		result.e30 = (e12 * e21 * e30 - e11 * e22 * e30 - e12 * e20 * e31 + e10 * e22 * e31 + e11 * e20 * e32 - e10 * e21 * e32) * invDet;
		result.e31 = (e01 * e22 * e30 - e02 * e21 * e30 + e02 * e20 * e31 - e00 * e22 * e31 - e01 * e20 * e32 + e00 * e21 * e32) * invDet;
		result.e32 = (e02 * e11 * e30 - e01 * e12 * e30 - e02 * e10 * e31 + e00 * e12 * e31 + e01 * e10 * e32 - e00 * e11 * e32) * invDet;
		result.e33 = (e01 * e12 * e20 - e02 * e11 * e20 + e02 * e10 * e21 - e00 * e12 * e21 - e01 * e10 * e22 + e00 * e11 * e22) * invDet;

		return result;
	}


	Matrix4x4 Matrix4x4::Identity() noexcept
	{
		return Matrix4x4
		{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f,
		};
	}

	float Matrix4x4::Determinant() noexcept
	{
		float det =
			e00 * e11 * e22 * e33 + 
			e00 * e12 * e23 * e31 + 
			e00 * e13 * e21 * e32 + 
			e01 * e10 * e23 * e32 + 
			e01 * e12 * e20 * e33 + 
			e01 * e13 * e22 * e30 + 
			e02 * e10 * e21 * e33 + 
			e02 * e11 * e23 * e30 + 
			e02 * e13 * e20 * e31 + 
			e03 * e10 * e22 * e31 + 
			e03 * e11 * e20 * e32 + 
			e03 * e12 * e21 * e30 - 
			e00 * e11 * e23 * e32 - 
			e00 * e12 * e21 * e33 - 
			e00 * e13 * e22 * e31 - 
			e01 * e10 * e22 * e33 - 
			e01 * e12 * e23 * e30 -
			e01 * e13 * e20 * e32 - 
			e02 * e10 * e23 * e31 - 
			e02 * e11 * e20 * e33 - 
			e02 * e13 * e21 * e30 - 
			e03 * e10 * e21 * e32 - 
			e03 * e11 * e22 * e30 - 
			e03 * e12 * e20 * e31;

		return det;
	}

	float Matrix4x4::Determinant3x3() noexcept
	{
		return 
			e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]) -
			e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0]) +
			e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
	}

	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const noexcept
	{
		return Matrix4x4{
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
		};
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

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) noexcept
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