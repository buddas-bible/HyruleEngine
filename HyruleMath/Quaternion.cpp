#include "Quaternion.h"

#include <cmath>
#include <utility>

#include "HRMathFunc.h"
#include "HRMatrix.h"
#include "HRVector.h"
#include "HRConstant.h"

namespace Hyrule
{
	Quaternion::Quaternion(float _w, float _x, float _y, float _z) noexcept
		:
		e{ _w, _x, _y, _z }
	{

	}

	Quaternion::operator Matrix1x4() noexcept
	{
		return Matrix1x4{ x, y, z, w };
	}

	Quaternion::operator Vector4D() noexcept
	{
		return Vector4D{ x, y, z, w };
	}

	Quaternion Quaternion::Identity() noexcept
	{
		return Quaternion{ 1.f, 0.f, 0.f, 0.f };
	}

	float Quaternion::Length() const noexcept
	{
		return powf(x * x + y * y + z * z + w * w, 0.5f);
	}

	float Quaternion::LengthSquare() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	float Quaternion::FastInvSqrt(float number) const noexcept
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

	/// <summary>
	/// »ç¿ø¼ö ³»Àû
	/// </summary>
	float Quaternion::Dot(const Quaternion& other) const noexcept
	{
		return (this->w * other.w) + (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
	}

	/// <summary>
	/// »ç¿ø¼ö ÄÓ·¹
	/// </summary>
	Quaternion Quaternion::Conjugate() const noexcept
	{
		return Quaternion{ w, -x, -y, -z };
	}

	/// <summary>
	/// »ç¿ø¼ö ¿ª¼ö
	/// </summary>
	Quaternion Quaternion::Inverse() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = 1 / temp;
			
		return Quaternion
		(
			w * invSqrt,
			-x * invSqrt, 
			-y * invSqrt, 
			-z * invSqrt
		);
	}

	Quaternion& Quaternion::Normalize() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		w *= invSqrt;
		x *= invSqrt;
		y *= invSqrt;
		z *= invSqrt;

		return *this;
	}
	
	Quaternion Quaternion::Normalized() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return Quaternion(*this);
		}

		float invSqrt = FastInvSqrt(temp);

		return Quaternion
		(
			w * invSqrt,
			x * invSqrt, 
			y * invSqrt, 
			z * invSqrt
		);
	}

	/// <summary>
	/// ¿ÀÀÏ·¯ °¢À¸·Î º¯È¯
	/// </summary>
	Vector3D Quaternion::ToEuler() const noexcept
	{
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;
		const float w2 = w * w;

		Vector3D euler;

		// Roll (X-axis rotation)
		const float sinRoll = 2.0f * (w * x + y * z);
		const float cosRoll = w2 - x2 - y2 + z2;
		euler.x = std::atan2(sinRoll, cosRoll);

		// Pitch (Y-axis rotation)
		const float sinPitch = 2.0f * (w * y - z * x);
		euler.y = std::asin(sinPitch);

		// Yaw (Z-axis rotation)
		const float sinYaw = 2.0f * (w * z + x * y);
		const float cosYaw = w2 + x2 - y2 - z2;
		euler.z = std::atan2(sinYaw, cosYaw);

		return euler;
	}

	/// <summary>
	/// Ãà°¢À¸·Î º¯È¯
	/// </summary>
	Vector4D Quaternion::ToAxisAngle() const noexcept
	{
		float squaredLength = LengthSquare();

		if (squaredLength < Epsilon)
		{
			// Quaternion represents no rotation, return zero axis and angle
			return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
		}

		float inverseLength = 1.0f / std::sqrt(squaredLength);
		float angle = 2.0f * std::acos(w);
		float sinAngle = std::sqrt(1.0f - w * w) * inverseLength;

		return Vector4D(x * inverseLength, y * inverseLength, z * inverseLength, angle);
	}

	/// <summary>
	/// È¸Àü Çà·Ä·Î º¯È¯
	/// </summary>
	Matrix4x4 Quaternion::ToMatrix() const noexcept
	{
		Matrix4x4 matrix;

		const float w2 = w * w;
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;
		const float xy = x * y;
		const float xz = x * z;
		const float yz = y * z;
		const float wx = w * x;
		const float wy = w * y;
		const float wz = w * z;

		matrix.e00 = 1.0f - 2.0f * (y2 + z2);
		matrix.e01 = 2.0f * (xy - wz);
		matrix.e02 = 2.0f * (xz + wy);
		matrix.e03 = 0.0f;

		matrix.e10 = 2.0f * (xy + wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz - wx);
		matrix.e13 = 0.0f;

		matrix.e20 = 2.0f * (xz - wy);
		matrix.e21 = 2.0f * (yz + wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);
		matrix.e23 = 0.0f;

		matrix.e30 = 0.0f;
		matrix.e31 = 0.0f;
		matrix.e32 = 0.0f;
		matrix.e33 = 1.0f;

		return matrix;

	}

	/// <summary>
	/// »ç¿ø¼ö µ¡¼À
	/// </summary>
	Quaternion& Quaternion::operator+=(const Quaternion& other) noexcept
	{
		this->w += other.w;
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö »¬¼À
	/// </summary>
	Quaternion& Quaternion::operator-=(const Quaternion& other) noexcept
	{
		this->w -= other.w;
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const noexcept
	{
		return Quaternion
		(
			this->w + other.w, 
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
		);
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const noexcept
	{
		return Quaternion
		(
			this->w - other.w,
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
		);
	}

	Quaternion Quaternion::operator-() const noexcept
	{
		return Quaternion
		(
			-this->w,
			-this->x,
			-this->y,
			-this->z
		);
	}

	/// <summary>
	/// »ç¿ø¼ö °ö¼À
	/// </summary>
	Quaternion& Quaternion::operator*=(const Quaternion& other) noexcept
	{
		// ÇØ¹ÐÅÏ °ö
		float newW = 
			this->w * other.w - 
			this->x * other.x - 
			this->y * other.y - 
			this->z * other.z;

		float newX = 
			this->w * other.x + 
			this->x * other.w +
			this->y * other.z -
			this->z * other.y;

		float newY = 
			this->w * other.y - 
			this->x * other.z + 
			this->y * other.w + 
			this->z * other.x;

		float newZ = 
			this->w * other.z + 
			this->x * other.y - 
			this->y * other.x + 
			this->z * other.w;

		this->w = newW;
		this->x = newX;
		this->y = newY;
		this->z = newZ;

		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö ³ª´°¼À
	/// </summary>
	Quaternion& Quaternion::operator/=(const Quaternion& other) noexcept
	{
		Quaternion conjugate = other.Conjugate();
		float temp = other.LengthSquare();

		/// »ç¿ø¼ö ³ª´°¼ÀÀº ÇØ´ç »ç¿ø¼öÀÇ ÄÓ·¹¸¦ °öÇÏ°í
		*this *= conjugate;

		/// Å©±âÀÇ Á¦°öÀ» ³ª´« °Í°ú °°´Ù.
		*this /= temp;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
	{
		Quaternion result = *this;
		result *= other;
		return result;
	}

	Quaternion Quaternion::operator/(const Quaternion& other) const noexcept
	{
		Quaternion result = *this;
		result /= other;
		return result;
	}
	
	/// <summary>
	/// »ç¿ø¼ö ½ºÄ®¶ó °ö¼À
	/// </summary>
	Quaternion& Quaternion::operator*=(const float n) noexcept
	{
		this->w *= n;
		this->x *= n;
		this->y *= n;
		this->z *= n;

		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö ½ºÄ®¶ó ³ª´°¼À
	/// </summary>
	Quaternion& Quaternion::operator/=(const float n) noexcept
	{
		float invN = 1.0f / n;

		this->w *= invN;
		this->x *= invN;
		this->y *= invN;
		this->z *= invN;

		return *this;
	}

	Quaternion Quaternion::operator*(const float n) const noexcept
	{
		Quaternion result(*this);

		result *= n;

		return result;
	}

	Quaternion Quaternion::operator/(const float n) const noexcept
	{
		Quaternion result(*this);

		result /= n;

		return result;
	}

	bool Quaternion::operator==(const Quaternion& other) const noexcept
	{
		return (this->w == other.w && this->x == other.x && this->y == other.y && this->z == other.z);
	}


	Quaternion operator*=(const float n, Quaternion& other) noexcept
	{
		other.w *= n;
		other.x *= n;
		other.y *= n;
		other.z *= n;

		return other;
	}

	Quaternion operator/=(const float n, Quaternion& other) noexcept
	{
		float invN = 1.0f / n;

		other.w *= invN;
		other.x *= invN;
		other.y *= invN;
		other.z *= invN;

		return other;
	}

	Quaternion operator*(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		result *= n;

		return result;
	}

	Quaternion operator/(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		result /= n;

		return result;
	}
}