#include "Vector4D.h"

#include <cmath>
#include <utility>

// #include "Vector3D.h"
#include "Matrix1x4.h"
#include "Quaternion.h"

namespace Hyrule
{
	Vector4D::Vector4D(float _x, float _y, float _z, float _w) noexcept
		: e{ _x, _y, _z, _w }
	{

	}

	Vector4D::operator Matrix1x4() noexcept
	{
		return Matrix1x4{ e[0], e[1] , e[2] , e[3] };
	}

	Vector4D::operator Quaternion() noexcept
	{
		return Quaternion{ w, x, y, z };
	}

	float Vector4D::Length() const noexcept
	{
		return powf(x * x + y * y + z * z + w * w, 0.5f);
	}

	float Vector4D::LengthSquare() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	Vector4D Vector4D::Cross(const Vector4D& other) const noexcept
	{
		return Vector4D(
			(this->y * other.z - this->z * other.y),
			(this->z * other.x - this->x * other.z),
			(this->x * other.y - this->y * other.x),
			0.f
		);
	}

	float Vector4D::Dot(const Vector4D& other) const noexcept
	{
		return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
	}

	float Vector4D::FastInvSqrt(float number) const noexcept
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5f;

		x2 = number * 0.5f;
		y = number;
		i = *(long*)&y;
		//	i = 0x5f3759df - (i >> 1);
		i = 0x5f375a86 - (i >> 1);
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));
		//	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

		return y;
	}

	Vector4D& Vector4D::Normalize() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		x *= invSqrt;
		y *= invSqrt;
		z *= invSqrt;
		w *= invSqrt;

		return *this;
	}

	Vector4D Vector4D::Normalized() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			// 원래는 영벡터를 반환했었지만
			// Normalize가 정규화 되지 않은 자기 자신을 반환하는 경우가 있으니
			// 자신을 복사해서 반환하는 것으로 함.
			return Vector4D(*this);		
			// return Vector4D(0.f, 0.f, 0.f, 0.f);
		}

		float invSqrt = FastInvSqrt(temp);

		return Vector4D
		(
			x * invSqrt, 
			y * invSqrt, 
			z * invSqrt, 
			w * invSqrt
		);
	}

	float Vector4D::Dot3(const Vector4D& other) const noexcept
	{
		return this->x * other.x + this->y * other.y + this->z * other.z;
	}

	Vector4D& Vector4D::Normalize3() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);
		x *= invSqrt;
		y *= invSqrt;
		z *= invSqrt;
		w = 0.f;

		return *this;
	}

	Vector4D Vector4D::Normalized3() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			// 원래는 영벡터를 반환했었지만
			// Normalize가 정규화 되지 않은 자기 자신을 반환하는 경우가 있으니
			// 자신을 복사해서 반환하는 것으로 함.
			auto v = Vector4D(*this);
			v.w = 0.f;

			return v;
			// return Vector4D(0.f, 0.f, 0.f, 0.f);
		}

		float invSqrt = FastInvSqrt(temp);

		return Vector4D(x * invSqrt, y * invSqrt, z * invSqrt, 0.f);
	}

	Vector4D& Vector4D::operator+=(const Vector4D& other) noexcept
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;

		return *this;
	}

	Vector4D& Vector4D::operator-=(const Vector4D& other) noexcept
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;

		return *this;
	}

	Vector4D Vector4D::operator+(const Vector4D& other) const noexcept
	{
		return Vector4D
		(
			this->x + other.x, 
			this->y + other.y, 
			this->z + other.z, 
			this->w + other.w
		);
	}

	Vector4D Vector4D::operator-(const Vector4D& other) const noexcept
	{
		return Vector4D
		(
			this->x - other.x, 
			this->y - other.y, 
			this->z - other.z, 
			this->w - other.w
		);
	}

	Vector4D Vector4D::operator-() const noexcept
	{
		return Vector4D
		(
			-this->x,
			-this->y,
			-this->z,
			-this->w
		);
	}

	Vector4D& Vector4D::operator*=(const float n) noexcept
	{
		this->x *= n;
		this->y *= n;
		this->z *= n;

		return *this;
	}

	Vector4D& Vector4D::operator/=(const float n) noexcept
	{
		float invN = 1.f / n;
		this->x *= invN;
		this->y *= invN;
		this->z *= invN;
		this->w *= invN;

		return *this;
	}

	Vector4D Vector4D::operator*(const float n) const noexcept
	{
		Vector4D temp;
		temp.x = this->x * n;
		temp.y = this->y * n;
		temp.z = this->z * n;
		temp.w = this->w * n;

		return temp;
	}

	Vector4D Vector4D::operator/(const float n) const noexcept
	{
		float invN = 1.f / n;

		Vector4D temp;
		temp.x = this->x * invN;
		temp.y = this->y * invN;
		temp.z = this->z * invN;
		temp.w = this->w * invN;

		return temp;
	}

	bool Vector4D::operator==(const Vector4D& other) const noexcept
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
	}
}