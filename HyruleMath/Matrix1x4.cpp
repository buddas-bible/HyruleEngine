#include "Vector4D.h"

#include "Matrix1x4.h"

namespace Hyrule
{
// 	constexpr Matrix1x4::Matrix1x4() noexcept :
// 		e{}
// 	{
// 
// 	}
// 
// 	constexpr Matrix1x4::Matrix1x4(float _e00, float _e01, float _e02, float _e03) noexcept : 
// 		e{ _e00, _e01, _e02, _e03 }
// 	{
// 
// 	}

	Matrix1x4::operator Vector4D() noexcept
	{
		return Vector4D{ this->e00, this->e01, this->e02, this->e03 };
	}

	Matrix1x4& Matrix1x4::operator+=(const Matrix1x4& other) noexcept
	{
		this->m = _mm_add_ps(this->m, other.m);

		return *this;
	}

	Matrix1x4& Matrix1x4::operator-=(const Matrix1x4& other) noexcept
	{
		this->m = _mm_sub_ps(this->m, other.m);

		return *this;
	}

	Matrix1x4 Matrix1x4::operator+(const Matrix1x4& other) const noexcept
	{
		return Matrix1x4(*this) += other;
	}

	Matrix1x4 Matrix1x4::operator-(const Matrix1x4& other) const noexcept
	{
		return Matrix1x4(*this) -= other;
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
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));

		return *this;
	}

	Matrix1x4& Matrix1x4::operator/=(const float n) noexcept
	{
		this->m = _mm_div_ps(this->m, _mm_set_ps1(n));

		return *this;
	}

	Matrix1x4 Matrix1x4::operator*(const float n) const noexcept
	{
		Matrix1x4 temp(*this);

		return temp *= n;
	}

	Matrix1x4 Matrix1x4::operator/(const float n) const noexcept
	{
		Matrix1x4 temp(*this);

		return temp /= n;
	}
}