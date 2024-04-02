#include <cmath>
#include <utility>

#include "Vector4D.h"

#include "Quaternion.h"

namespace Hyrule
{
// 	Quaternion::Quaternion() :
// 		x(), y(), z(), w()
// 	{
// 	
// 	}
// 
// 	constexpr Quaternion::Quaternion(float _w, float _x, float _y, float _z) :
// 		x(_x), y(_y), z(_z), w(_w)
// 	{
// 
// 	}

	Quaternion::operator Vector4D()
	{
		return Vector4D{ x, y, z, w };
	}

	float Quaternion::Length() const
	{
		return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(m, m, 0xff)));
	}

	float Quaternion::LengthSquare() const
	{
		// ÀÌ°Ç ¼Óµµ°¡ ¶È°°¾ÒÀ½.
		// return x * x + y * y + z * z + w * w;
		return _mm_cvtss_f32(_mm_dp_ps(m, m, 0xff));
	}

	float Quaternion::FastInvSqrt(float number) const
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

		// ¹º ¿ªÁ¦°ö±ÙÀÌ¿©¤»¤»¤»
		return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set_ps1(number)));
	}

	/// <summary>
	/// »ç¿ø¼ö ³»Àû
	/// </summary>
	float Quaternion::Dot(const Quaternion& other) const
	{
		// return (this->w * other.w) + (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
		return _mm_cvtss_f32(_mm_dp_ps(this->m, other.m, 0xff));
	}

	/// <summary>
	/// »ç¿ø¼ö ÄÓ·¹
	/// </summary>
	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion{ w, -x, -y, -z };
	}

	/// <summary>
	/// »ç¿ø¼ö ¿ª¼ö
	/// </summary>
	Quaternion Quaternion::Inverse() const
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

	Quaternion& Quaternion::Normalize()
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
	
	Quaternion Quaternion::Normalized() const
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
	/// »ç¿ø¼ö µ¡¼À
	/// </summary>
	Quaternion& Quaternion::operator+=(const Quaternion& other)
	{
		// this->w += other.w;
		// this->x += other.x;
		// this->y += other.y;
		// this->z += other.z;
		this->m = _mm_add_ps(this->m, other.m);
		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö »¬¼À
	/// </summary>
	Quaternion& Quaternion::operator-=(const Quaternion& other)
	{
		// this->w -= other.w;
		// this->x -= other.x;
		// this->y -= other.y;
		// this->z -= other.z;
		this->m = _mm_sub_ps(this->m, other.m);
		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const
	{
		Quaternion temp(*this);
		return temp += other;
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const
	{
		Quaternion temp(*this);
		return temp -= other;
	}

	Quaternion Quaternion::operator-() const
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
	Quaternion& Quaternion::operator*=(const Quaternion& other)
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
	Quaternion& Quaternion::operator/=(const Quaternion& other)
	{
		Quaternion conjugate = other.Conjugate();
		float temp = other.Length();

		/// »ç¿ø¼ö ³ª´°¼ÀÀº ÇØ´ç »ç¿ø¼öÀÇ ÄÓ·¹¸¦ °öÇÏ°í
		*this *= conjugate;

		/// Å©±âÀÇ Á¦°öÀ» ³ª´« °Í°ú °°´Ù.
		*this /= temp;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		Quaternion result = *this;
		result *= other;
		return result;
	}

	Quaternion Quaternion::operator/(const Quaternion& other) const
	{
		Quaternion result = *this;
		result /= other;
		return result;
	}
	
	/// <summary>
	/// »ç¿ø¼ö ½ºÄ®¶ó °ö¼À
	/// </summary>
	Quaternion& Quaternion::operator*=(const float n)
	{
		// this->w *= n;
		// this->x *= n;
		// this->y *= n;
		// this->z *= n;
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));
		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö ½ºÄ®¶ó ³ª´°¼À
	/// </summary>
	Quaternion& Quaternion::operator/=(const float n)
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

	Quaternion Quaternion::operator*(const float n) const
	{
		Quaternion result(*this);

		return result *= n;
	}

	Quaternion Quaternion::operator/(const float n) const
	{
		Quaternion result(*this);

		return result /= n;
	}

	bool Quaternion::operator==(const Quaternion& other) const
	{
		return (this->w == other.w && this->x == other.x && this->y == other.y && this->z == other.z);
	}


	Quaternion operator*=(const float n, Quaternion& other)
	{
		// other.w *= n;
		// other.x *= n;
		// other.y *= n;
		// other.z *= n;
		return other *= n;
	}

	Quaternion operator/=(const float n, Quaternion& other)
	{
		// float invN = 1.0f / n;
		// 
		// other.w *= invN;
		// other.x *= invN;
		// other.y *= invN;
		// other.z *= invN;
		return other /= n;
	}

	Quaternion operator*(const float n, const Quaternion& other)
	{
		Quaternion result(other);

		return result *= n;
	}

	Quaternion operator/(const float n, const Quaternion& other)
	{
		Quaternion result(other);

		return result /= n;
	}
}