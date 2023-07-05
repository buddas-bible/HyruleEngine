#include "Quaternion.h"

#include <cmath>
#include <utility>

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix1x4.h"
#include "Matrix4x4.h"
#include "HRConstant.h"

namespace Hyrule
{
	constexpr Quaternion::Quaternion() noexcept : 
		w(), x(), y(), z()
	{

	}

	constexpr Quaternion::Quaternion(float _w, float _x, float _y, float _z) noexcept :
		e{ _w, _x, _y, _z }
	{

	}

	constexpr Quaternion::operator Matrix1x4() noexcept
	{
		return Matrix1x4{ x, y, z, w };
	}

	constexpr Quaternion::operator Vector4D() noexcept
	{
		return Vector4D{ x, y, z, w };
	}

	float Quaternion::Length() const noexcept
	{
		return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(m, m, 0xff)));
	}

	float Quaternion::LengthSquare() const noexcept
	{
		// 이건 속도가 똑같았음.
		// return x * x + y * y + z * z + w * w;
		return _mm_cvtss_f32(_mm_dp_ps(m, m, 0xff));
	}

	float Quaternion::FastInvSqrt(float number) const noexcept
	{
		// long i;
		// float x2, y;
		// const float threehalfs = 1.5f;
		// 
		// x2 = number * 0.5f;
		// y = number;
		// i = *(long*)&y;
		// //	i = 0x5f3759df - (i >> 1);
		// i = 0x5f375a86 - (i >> 1);
		// y = *(float*)&i;
		// y = y * (threehalfs - (x2 * y * y));
		// //	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
		// return y;

		// 뭔 역제곱근이여ㅋㅋㅋ
		return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set_ps1(number)));
	}

	/// <summary>
	/// 사원수 내적
	/// </summary>
	float Quaternion::Dot(const Quaternion& other) const noexcept
	{
		// return (this->w * other.w) + (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
		return _mm_cvtss_f32(_mm_dp_ps(this->m, other.m, 0xff));
	}

	/// <summary>
	/// 사원수 켤레
	/// </summary>
	Quaternion Quaternion::Conjugate() const noexcept
	{
		return Quaternion{ w, -x, -y, -z };
	}

	/// <summary>
	/// 사원수 역수
	/// </summary>
	Quaternion Quaternion::Inverse() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);
			
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

		// w *= invSqrt;
		// x *= invSqrt;
		// y *= invSqrt;
		// z *= invSqrt;

		this->m = _mm_mul_ps(
			this->m, 
			_mm_set_ps1(invSqrt)
		);

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

		Quaternion q{ *this };

		q.m = _mm_mul_ps(
			this->m,
			_mm_set_ps1(invSqrt)
		);

		return q;
	}

	/// <summary>
	/// 오일러 각으로 변환
	/// </summary>
	Vector3D Quaternion::ToEuler() const noexcept
	{
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;
		const float w2 = w * w;

		Vector3D euler;

		// Roll (Z-axis rotation)
		float sinRoll = 2.0f * (w * x + y * z);
		float cosRoll = w2 - x2 - y2 + z2;
		euler.x = std::atan2f(sinRoll, cosRoll);

		// Pitch (X-axis rotation)
		float sinPitch = 2.0f * (w * y - z * x);
		euler.y = std::asinf(sinPitch);

		// Yaw (Y-axis rotation)
		float sinYaw = 2.0f * (w * z + x * y);
		float cosYaw = w2 + x2 - y2 - z2;
		euler.z = std::atan2f(sinYaw, cosYaw);

		return euler;
	}

	/// <summary>
	/// 축각으로 변환
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
	/// 회전 행렬로 변환
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
		matrix.e01 = 2.0f * (xy + wz);
		matrix.e02 = 2.0f * (xz - wy);
		matrix.e03 = 0.0f;

		matrix.e10 = 2.0f * (xy - wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz + wx);
		matrix.e13 = 0.0f;

		matrix.e20 = 2.0f * (xz + wy);
		matrix.e21 = 2.0f * (yz - wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);
		matrix.e23 = 0.0f;

		matrix.e30 = 0.0f;
		matrix.e31 = 0.0f;
		matrix.e32 = 0.0f;
		matrix.e33 = 1.0f;

		return matrix;
	}

	/// <summary>
	/// 사원수 덧셈
	/// </summary>
	Quaternion& Quaternion::operator+=(const Quaternion& other) noexcept
	{
		// this->w += other.w;
		// this->x += other.x;
		// this->y += other.y;
		// this->z += other.z;
		this->m = _mm_add_ps(this->m, other.m);
		return *this;
	}

	/// <summary>
	/// 사원수 뺄셈
	/// </summary>
	Quaternion& Quaternion::operator-=(const Quaternion& other) noexcept
	{
		// this->w -= other.w;
		// this->x -= other.x;
		// this->y -= other.y;
		// this->z -= other.z;
		this->m = _mm_sub_ps(this->m, other.m);
		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const noexcept
	{
		Quaternion temp(*this);
		return temp += other;
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const noexcept
	{
		Quaternion temp(*this);
		return temp -= other;
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
	/// 사원수 곱셈
	/// </summary>
	Quaternion& Quaternion::operator*=(const Quaternion& other) noexcept
	{
		// 해밀턴 곱
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
	/// 사원수 나눗셈
	/// </summary>
	Quaternion& Quaternion::operator/=(const Quaternion& other) noexcept
	{
		Quaternion conjugate = other.Conjugate();
		float temp = other.LengthSquare();

		/// 사원수 나눗셈은 해당 사원수의 켤레를 곱하고
		*this *= conjugate;

		/// 크기의 제곱을 나눈 것과 같다.
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
	/// 사원수 스칼라 곱셈
	/// </summary>
	Quaternion& Quaternion::operator*=(const float n) noexcept
	{
		// this->w *= n;
		// this->x *= n;
		// this->y *= n;
		// this->z *= n;
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));
		return *this;
	}

	/// <summary>
	/// 사원수 스칼라 나눗셈
	/// </summary>
	Quaternion& Quaternion::operator/=(const float n) noexcept
	{
		// float invN = 1.0f / n;
		// 
		// this->w *= invN;
		// this->x *= invN;
		// this->y *= invN;
		// this->z *= invN;
		this->m = _mm_div_ps(this->m, _mm_set_ps1(n));
		return *this;
	}

	Quaternion Quaternion::operator*(const float n) const noexcept
	{
		Quaternion result(*this);

		return result *= n;
	}

	Quaternion Quaternion::operator/(const float n) const noexcept
	{
		Quaternion result(*this);

		return result /= n;
	}

	bool Quaternion::operator==(const Quaternion& other) const noexcept
	{
		return (this->w == other.w && this->x == other.x && this->y == other.y && this->z == other.z);
	}


	Quaternion operator*=(const float n, Quaternion& other) noexcept
	{
		// other.w *= n;
		// other.x *= n;
		// other.y *= n;
		// other.z *= n;
		return other *= n;
	}

	Quaternion operator/=(const float n, Quaternion& other) noexcept
	{
		// float invN = 1.0f / n;
		// 
		// other.w *= invN;
		// other.x *= invN;
		// other.y *= invN;
		// other.z *= invN;
		return other /= n;
	}

	Quaternion operator*(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		return result *= n;
	}

	Quaternion operator/(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		return result /= n;
	}
}