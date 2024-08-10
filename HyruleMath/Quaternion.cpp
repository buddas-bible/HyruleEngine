#include <istream>
#include <ostream>
#include <cmath>
#include <utility>

#include "Vector4D.hh"
#include "Vector3D.hh"
#include "HRConstant.h"

#include "Quaternion.hh"

#include <sstream>

namespace Hyrule
{
	Quaternion::operator Vector4D() noexcept
	{
		return Vector4D{ x, y, z, w };
	}

	float Quaternion::Length() const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(m, m, 0xff)));
#else
        return std::sqrtf(x * x + y * y + z * z + w * w);
#endif
    }

	float Quaternion::LengthSquare() const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_dp_ps(m, m, 0xff));
#else
        return x * x + y * y + z * z + w * w;
#endif
    }

	float Quaternion::FastInvSqrt(float number) const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set_ps1(number)));
#else
        return 1 / std::sqrtf(number);
#endif
	}

	/// <summary>
	/// »ç¿ø¼ö ³»Àû
	/// </summary>
	float Quaternion::Dot(const Quaternion& other) const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_dp_ps(this->m, other.m, 0xff));
#else
		return (this->w * other.w) + (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
#endif
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

#ifdef _PHYSICS
        this->m = _mm_mul_ps(
            this->m,
            _mm_set_ps1(invSqrt)
        );
#else
// 		w *= invSqrt;
// 		x *= invSqrt;
// 		y *= invSqrt;
// 		z *= invSqrt;
        (*this) *= invSqrt;
#endif


		return *this;
	}
	
	Quaternion Quaternion::Normalized() const noexcept
	{
        Quaternion q(*this);

		return q.Normalize();
	}

	/// <summary>
	/// »ç¿ø¼ö µ¡¼À
	/// </summary>
	Quaternion& Quaternion::operator+=(const Quaternion& other) noexcept
	{
#ifdef _PHYSICS
		this->m = _mm_add_ps(this->m, other.m);
#else
        this->w += other.w;
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
#endif
		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö »¬¼À
	/// </summary>
	Quaternion& Quaternion::operator-=(const Quaternion& other) noexcept
	{
#ifdef _PHYSICS
		this->m = _mm_sub_ps(this->m, other.m);
#else
        this->w -= other.w;
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
#endif
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
#ifdef _PHYSICS
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));
#else
        this->w *= n;
        this->x *= n;
        this->y *= n;
        this->z *= n;
#endif
		return *this;
	}

	/// <summary>
	/// »ç¿ø¼ö ½ºÄ®¶ó ³ª´°¼À
	/// </summary>
	Quaternion& Quaternion::operator/=(const float n) noexcept
	{
#ifdef _PHYSICS
		this->m = _mm_div_ps(this->m, _mm_set_ps1(n));
#else
        float invN = 1.0f / n;

        this->w *= invN;
        this->x *= invN;
        this->y *= invN;
        this->z *= invN;
#endif
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
		return other *= n;
	}

	Quaternion operator/=(const float n, Quaternion& other) noexcept
	{
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

    std::ostream& operator<<(std::ostream& out, const Quaternion& point) noexcept
    {

        out << (std::fabs(point.w) > 0.001 ? point.w : 0) << " ";
        out << (std::fabs(point.x) > 0.001 ? point.x : 0) << " ";
        out << (std::fabs(point.y) > 0.001 ? point.y : 0) << " ";
        out << (std::fabs(point.z) > 0.001 ? point.z : 0);

        return out;
    }

   std::istream& operator>>(std::istream& in, Quaternion& point) noexcept
   {
       in >> point.w >> point.x >> point.y >> point.z;
       //¹ÞÀº Vector3¿¡ xyz¸¦ ¹Þ°í point¿¡ º¯È¯ÇØ¼­ Áý¾î³Ö±â
       return in;
   }

   std::string Quaternion::ToString() noexcept
   {
       std::ostringstream out;
       out << (abs(w) > 0.001 ? w : 0) << " ";
       out << (abs(x) > 0.001 ? x : 0) << " ";
       out << (abs(y) > 0.001 ? y : 0) << " ";
       out << (abs(z) > 0.001 ? z : 0);
       return out.str();
   }
}
