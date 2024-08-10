#include <cmath>
#include <utility>

#include "Vector3D.hh"
#include "Matrix1x4.h"
#include "Matrix4x4.h"
#include "Quaternion.hh"
#include "Vector4D.hh"

#include <sstream>

namespace Hyrule
{
	Vector4D::Vector4D(const Vector3D& _other, const float _w) noexcept
		: x{ _other.x }, y{ _other.y }, z{ _other.z }, w{ _w }
	{

	}

	Vector4D::operator Matrix1x4() noexcept
	{
#ifdef _PHYSICS
		return Matrix1x4{ e[0], e[1] , e[2] , e[3] };
#else
        return Matrix1x4{ x, y, z, w };
#endif
	}

	Vector4D::operator Quaternion() noexcept
	{
		return Quaternion{ w, x, y, z };
	}

	float Vector4D::Length() const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(m, m, 0xff)));
#else
        return std::powf(x * x + y * y + z * z + w * w, 0.5f);
#endif
	}

	float Vector4D::LengthSquare() const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_dp_ps(m, m, 0xff));
#else
        return x * x + y * y + z * z + w * w;
#endif
	}

	Vector4D Vector4D::Cross(const Vector4D& other) const noexcept
	{
#ifdef _PHYSICS
		__m128 m1 = _mm_shuffle_ps(
			this->m,
			this->m,
			_MM_SHUFFLE(3, 0, 2, 1)		// Y Z X 0
		);

		__m128 m2 = _mm_shuffle_ps(
			other.m,
			other.m,
			_MM_SHUFFLE(3, 0, 2, 1)
		);

		m1 = _mm_mul_ps(m2, this->m);
		m2 = _mm_mul_ps(m1, other.m);
		m1 = _mm_sub_ps(m1, m2);

		Vector4D temp;
		temp.m = _mm_shuffle_ps(m1, m1, _MM_SHUFFLE(3, 0, 2, 1));

		return temp;
#else
        return Vector4D(
            (this->y * other.z - this->z * other.y),
            (this->z * other.x - this->x * other.z),
            (this->x * other.y - this->y * other.x),
            0.f
        );
#endif
	}

	float Vector4D::Dot(const Vector4D& other) const noexcept
	{
#ifdef _PHYSICS
		// _mm_dp_ps는 각 요소를 곱해서 더해주는 기능
		// _mm_cvtss_f32는 스칼라만 뽑아주는 것.
		return _mm_cvtss_f32(_mm_dp_ps(this->m, other.m, 0xFF));
#else
        return x * other.x + y * other.y + z * other.z + w * other.w;
#endif
	}

	float Vector4D::FastInvSqrt(float number) const noexcept
	{
#ifdef _PHYSICS
		return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set_ps1(number)));
#else
        return 1 / powf(number, 0.5f);
#endif
	}

	Vector4D& Vector4D::Normalize() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
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
        (*this) *= invSqrt;
#endif

		return *this;
	}

	Vector4D Vector4D::Normalized() const noexcept
    {
		Vector4D vec(*this);

		return vec.Normalize();
	}

	float Vector4D::Dot3(const Vector4D& other) const noexcept
	{

#ifdef _PHYSICS
		Vector4D temp(*this);
		temp.w = 0.f;
		temp.m = _mm_dp_ps(temp.m, other.m, 0xFF);
		return temp.m.m128_f32[0];
#else
		return this->x * other.x + this->y * other.y + this->z * other.z;
#endif
	}

	Vector4D& Vector4D::Normalize3() noexcept
	{
        float _w = w;
        w = 0.f;

		float temp = LengthSquare();

		if (temp == 0)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

#ifdef _PHYSICS
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(invSqrt));
		w = _w;
#else
        (*this) *= invSqrt;
        w = _w;
#endif
		return *this;
	}

	Vector4D Vector4D::Normalized3() const noexcept
	{
        Vector4D vec(*this);

		return vec.Normalize3();
	}

	Vector4D& Vector4D::operator*=(const Matrix4x4& _mat) noexcept
	{
#ifdef _PHYSICS
		Matrix4x4 temp{ _mat.Transpose() };
		__m128 m128 = m;
	
		this->x = _mm_cvtss_f32(_mm_dp_ps(m128, temp.m[0].m, 0xFF));
		this->y = _mm_cvtss_f32(_mm_dp_ps(m128, temp.m[1].m, 0xFF));
		this->z = _mm_cvtss_f32(_mm_dp_ps(m128, temp.m[2].m, 0xFF));
		this->w = _mm_cvtss_f32(_mm_dp_ps(m128, temp.m[3].m, 0xFF));
#else
        Vector4D vec(*this);
        this->x = _mat.e00 * vec.x + _mat.e10 * vec.y + _mat.e20 * vec.z + _mat.e30 * vec.w;
        this->y = _mat.e01 * vec.x + _mat.e11 * vec.y + _mat.e21 * vec.z + _mat.e31 * vec.w;
        this->z = _mat.e02 * vec.x + _mat.e12 * vec.y + _mat.e22 * vec.z + _mat.e32 * vec.w;
        this->w = _mat.e03 * vec.x + _mat.e13 * vec.y + _mat.e23 * vec.z + _mat.e33 * vec.w;
#endif
        return *this;
	}
	
	Vector4D Vector4D::operator*(const Matrix4x4& _mat) const noexcept
	{
		Vector4D temp(*this);
	
		return temp *= _mat;
	}

	Vector4D& Vector4D::operator+=(const Vector4D& other) noexcept
	{
#ifdef _PHYSICS
		this->m = _mm_add_ps(this->m, other.m);
#else
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
#endif
        this->w = 0.f;

		return *this;
	}

	Vector4D& Vector4D::operator-=(const Vector4D& other) noexcept
	{
#ifdef _PHYSICS
		this->m = _mm_sub_ps(this->m, other.m);
#else
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
#endif
        this->w = 0.f;

		return *this;
	}

	Vector4D Vector4D::operator+(const Vector4D& other) const noexcept
	{
		Vector4D temp(*this);
		return temp += other;
	}

	Vector4D Vector4D::operator-(const Vector4D& other) const noexcept
	{
		Vector4D temp(*this);
		return temp -= other;
	}

	Vector4D Vector4D::operator-() const noexcept
	{
		return Vector4D
		(
			-this->w,
			-this->x,
			-this->y,
			-this->z
		);
	}

	Vector4D& Vector4D::operator*=(const float n) noexcept
	{
#ifdef _PHYSICS
        float _w = w;
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));
        w = _w;
#else
        this->x *= n;
        this->y *= n;
        this->z *= n;
#endif
		return *this;
	}

	Vector4D& Vector4D::operator/=(const float n) noexcept
	{
#ifdef _PHYSICS
        float _w = w;
		this->m = _mm_div_ps(this->m, _mm_set_ps1(n));
        w = _w;
#else
        this->x /= n;
        this->y /= n;
        this->z /= n;
#endif
		return *this;
	}

	Vector4D Vector4D::operator*(const float n) const noexcept
	{
		Vector4D temp(*this);
		return temp *= n;
	}

	Vector4D Vector4D::operator/(const float n) const noexcept
	{
		Vector4D temp(*this);
		return temp /= n;
	}

	bool Vector4D::operator==(const Vector4D& other) const noexcept
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
	}

    std::ostream& operator<<(std::ostream& out, const Vector4D& point) noexcept
    {
        out << (abs(point.x) > 0.001 ? point.x : 0) << " ";
        out << (abs(point.y) > 0.001 ? point.y : 0) << " ";
        out << (abs(point.z) > 0.001 ? point.z : 0) << " ";
        out << (abs(point.w) > 0.001 ? point.w : 0);
        return out;
    }

    std::istream& operator>>(std::istream& in, Vector4D& point) noexcept
    {
        in >> point.x >> point.y >> point.z >> point.w;
        return in;
    }

    std::string Vector4D::ToString() noexcept
    {
        std::ostringstream out;
        out << (abs(x) > 0.001 ? x : 0) << " ";
        out << (abs(y) > 0.001 ? y : 0) << " ";
        out << (abs(z) > 0.001 ? z: 0) << " ";
        out << (abs(w) > 0.001 ? w : 0);
        return out.str();
    }
}
