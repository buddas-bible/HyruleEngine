#include "Matrix1x4.h"

#include "Vector4D.h"

namespace Hyrule
{

	Matrix1x4::Matrix1x4(float _e00, float _e01, float _e02, float _e03) noexcept
		:
		e{ _e00, _e01, _e02, _e03 }
	{

	}

	Matrix1x4::operator Vector4D() noexcept
	{
		return Vector4D{ this->e00, this->e01, this->e02, this->e03 };
	}

	Matrix1x4& Matrix1x4::operator+=(const Matrix1x4& other) noexcept
	{
		this->e00 += other.e00;
		this->e01 += other.e01;
		this->e02 += other.e02;
		this->e03 += other.e03;

		return *this;
	}

	Matrix1x4& Matrix1x4::operator-=(const Matrix1x4& other) noexcept
	{
		this->e00 -= other.e00;
		this->e01 -= other.e01;
		this->e02 -= other.e02;
		this->e03 -= other.e03;

		return *this;
	}

	Matrix1x4 Matrix1x4::operator+(const Matrix1x4& other) const noexcept
	{
		return Matrix1x4
		{
			this->e00 + other.e00,
			this->e01 + other.e01,
			this->e02 + other.e02,
			this->e03 + other.e03
		};
	}

	Matrix1x4 Matrix1x4::operator-(const Matrix1x4& other) const noexcept
	{
		return Matrix1x4
		{
			this->e00 - other.e00,
			this->e01 - other.e01,
			this->e02 - other.e02,
			this->e03 - other.e03
		};
	}

	Matrix1x4 Matrix1x4::operator-() const noexcept
	{
		return Matrix1x4
		{
			-this->e00,
			-this->e01,
			-this->e02,
			-this->e03
		};
	}

	Matrix1x4& Matrix1x4::operator*=(const float n) noexcept
	{
		this->e00 *= n;
		this->e01 *= n;
		this->e02 *= n;
		this->e03 *= n;

		return *this;
	}

	Matrix1x4& Matrix1x4::operator/=(const float n) noexcept
	{
		float invN = 1.f / n;
		this->e00 *= invN;
		this->e01 *= invN;
		this->e02 *= invN;
		this->e03 *= invN;

		return *this;
	}

	Matrix1x4 Matrix1x4::operator*(const float n) const noexcept
	{
		Matrix1x4 temp;
		temp.e00 = this->e00 * n;
		temp.e01 = this->e01 * n;
		temp.e02 = this->e02 * n;
		temp.e03 = this->e03 * n;

		return temp;
	}

	Matrix1x4 Matrix1x4::operator/(const float n) const noexcept
	{
		float invN = 1.f / n;

		Matrix1x4 temp;
		temp.e00 = this->e00 * invN;
		temp.e01 = this->e01 * invN;
		temp.e02 = this->e02 * invN;
		temp.e03 = this->e03 * invN;

		return temp;
	}
}