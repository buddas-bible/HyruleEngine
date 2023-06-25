#include "Vector3D.h"

#include <cmath>
#include <utility>

#include "Vector4D.h"
#include "Matrix1x3.h"
#include "Quaternion.h"

namespace Hyrule
{
	Vector3D::Vector3D(float _x, float _y, float _z) noexcept 
		: e{ _x, _y, _z }
	{

	}

	Vector3D::operator Matrix1x3() noexcept
	{
		return Matrix1x3{ x, y, z };
	}

	float Vector3D::Length() const noexcept
	{
		return powf((x * x) + (y * y) + (z * z), 0.5);
	}

	float Vector3D::LengthSquare() const noexcept
	{
		return (x * x) + (y * y) + (z * z);
	}

	Vector3D Vector3D::Cross(const Vector3D& other) const noexcept
	{
		return Vector3D(
			(this->y * other.z - this->z * other.y),
			(this->z * other.x - this->x * other.z),
			(this->x * other.y - this->y * other.x));
	}

	float Vector3D::Dot(const Vector3D& other) const noexcept
	{
		return this->x * other.x + this->y * other.y + this->z * other.z;
	}

	float Vector3D::FastInvSqrt(float number) const noexcept
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

	Vector3D& Vector3D::Normalize() noexcept
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

		return *this;
	}

	Vector3D Vector3D::Normalized() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return Vector3D(*this);
			// return Vector3D(0.f, 0.f, 0.f);
		}

		float invSqrt = FastInvSqrt(temp);

		return Vector3D(x * invSqrt, y * invSqrt, z * invSqrt);
	}

	Vector3D& Vector3D::operator+=(const Vector3D& other) noexcept
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	Vector3D& Vector3D::operator-=(const Vector3D& other) noexcept
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	Vector3D Vector3D::operator+(const Vector3D& other) const noexcept
	{
		return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	Vector3D Vector3D::operator-(const Vector3D& other) const noexcept
	{
		return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3D Vector3D::operator-() const noexcept
	{
		return Vector3D(-x, -y, -z);
	}

	Vector3D& Vector3D::operator*=(const float n) noexcept
	{
		this->x *= n;
		this->y *= n;
		this->z *= n;

		return *this;
	}

	Vector3D& Vector3D::operator/=(const float n) noexcept
	{
		this->x /= n;
		this->y /= n;
		this->z /= n;

		return *this;
	}

	Vector3D Vector3D::operator*(const float n) const noexcept
	{
		Vector3D temp;
		temp.x = n * this->x;
		temp.y = n * this->y;
		temp.z = n * this->z;

		return temp;
	}

	Vector3D Vector3D::operator/(const float n) const noexcept
	{
		Vector3D temp;
		temp.x = this->x / n;
		temp.y = this->y / n;
		temp.z = this->z / n;

		return temp;
	}

	bool Vector3D::operator==(const Vector3D& other) const noexcept
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}

	Vector3D operator*(const Quaternion& q, const Vector3D& v) noexcept
	{
		Quaternion conjugate = q.Conjugate();
		Quaternion result = q * Quaternion(0.f, v.x, v.y, v.z) * conjugate;
		return Vector3D(result.x, result.y, result.z);
	}
}