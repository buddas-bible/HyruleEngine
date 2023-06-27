#include "Vector4D.h"

#include <cmath>
#include <utility>

#include "Vector3D.h"
#include "Matrix1x4.h"
#include "Quaternion.h"

namespace Hyrule
{
	constexpr Vector4D::Vector4D() noexcept : e{}
	{

	}

	constexpr Vector4D::Vector4D(float _x, float _y, float _z, float _w) noexcept
		: e{ _x, _y, _z, _w }
	{

	}


	constexpr Vector4D::Vector4D(const Vector3D& _other, float _w) noexcept
		: x{ _other.x }, y{ _other.y }, z{ _other.z }, w{ _w }
	{

	}

	constexpr Vector4D::operator Matrix1x4() noexcept
	{
		return Matrix1x4{ e[0], e[1] , e[2] , e[3] };
	}

	constexpr Vector4D::operator Quaternion() noexcept
	{
		return Quaternion{ w, x, y, z };
	}

	float Vector4D::Length() const noexcept
	{
		return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(m, m, 0xff)));
	}

	float Vector4D::LengthSquare() const noexcept
	{
		return _mm_cvtss_f32(_mm_dp_ps(m, m, 0xff));
	}

	Vector4D Vector4D::Cross(const Vector4D& other) const noexcept
	{
		// 시간 비교 해보니까 말도 안되게 시간이 오래걸려서 주석.
		// 		__m128 m1 = _mm_mul_ps(
		// 			this->m, 
		// 			_mm_shuffle_ps(
		// 				other.m, 
		// 				other.m, 
		// 				_MM_SHUFFLE(3, 0, 2, 1)
		// 			)
		// 		);
		// 
		// 		__m128 m2 = _mm_mul_ps(
		// 			_mm_shuffle_ps(
		// 				this->m, 
		// 				this->m,
		// 				_MM_SHUFFLE(3, 0, 2, 1)
		// 			), 
		// 			other.m
		// 		);
		// 
		// 		Vector4D temp;
		// 		temp.m = _mm_sub_ps(m1, m2);
		// 
		// 		return temp;

		return Vector4D(
			(this->y * other.z - this->z * other.y),
			(this->z * other.x - this->x * other.z),
			(this->x * other.y - this->y * other.x),
			0.f
 		);
	}

	float Vector4D::Dot(const Vector4D& other) const noexcept
	{
		// _mm_dp_ps는 각 요소를 곱해서 더해주는 기능
		// _mm_cvtss_f32는 스칼라만 뽑아주는 것.
		return _mm_cvtss_f32(_mm_dp_ps(this->m, other.m, 0xFF));
	}

	float Vector4D::FastInvSqrt(float number) const noexcept
	{
		// 	long i;
		// 	float x2, y;
		// 	const float threehalfs = 1.5f;
		// 
		// 	x2 = number * 0.5f;
		// 	y = number;
		// 	i = *(long*)&y;
		// 	//	i = 0x5f3759df - (i >> 1);
		// 	i = 0x5f375a86 - (i >> 1);
		// 	y = *(float*)&i;
		// 	y = y * (threehalfs - (x2 * y * y));
		// 	//	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
		return _mm_cvtss_f32(_mm_rsqrt_ps(_mm_set_ps1(number)));
	}

	Vector4D& Vector4D::Normalize() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		this->m = _mm_mul_ps(
			this->m, 
			_mm_set_ps1(invSqrt)
		);

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

		Vector4D vec(*this);

		vec.m = _mm_mul_ps(
			this->m, 
			_mm_set_ps1(invSqrt)
		);

		return vec;
	}

	float Vector4D::Dot3(const Vector4D& other) const noexcept
	{
		Vector4D temp(*this);

		temp.w = 0.f;

		temp.m = _mm_dp_ps(temp.m, other.m, 0xFF);

		return temp.m.m128_f32[0];

		// return this->x * other.x + this->y * other.y + this->z * other.z;
	}

	Vector4D& Vector4D::Normalize3() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		this->m = _mm_mul_ps(this->m, _mm_set_ps1(invSqrt));
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
		}

		float invSqrt = FastInvSqrt(temp);

		Vector4D vec(*this);

		vec.m = _mm_mul_ps(this->m, _mm_set_ps1(invSqrt));

		return vec;
	}

	Vector4D& Vector4D::operator+=(const Vector4D& other) noexcept
	{
		this->m = _mm_add_ps(this->m, other.m);

		return *this;
	}

	Vector4D& Vector4D::operator-=(const Vector4D& other) noexcept
	{
		this->m = _mm_sub_ps(this->m, other.m);

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
		// Vector4D temp;
		// temp.m = _mm_mul_ps(this->m, _mm_set_ps1(-1.f));
		// return temp;

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
		this->m = _mm_mul_ps(this->m, _mm_set_ps1(n));
		return *this;
	}

	Vector4D& Vector4D::operator/=(const float n) noexcept
	{
		this->m = _mm_div_ps(this->m, _mm_set_ps1(n));
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
}