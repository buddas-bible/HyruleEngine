// #include "Vector4D.h"

#include "Matrix4x4.h"
#include "Vector3D.hh"

namespace Hyrule
{
	Matrix4x4 Matrix4x4::Transpose() const noexcept
	{
		return Matrix4x4
		{
			e00, e10, e20, e30,
			e01, e11, e21, e31,
			e02, e12, e22, e32,
			e03, e13, e23, e33
		};
	}

	Matrix4x4 Matrix4x4::Inverse() const noexcept
	{
		Matrix4x4 result{};

		float det = Determinant();

		if (det == 0.0f)
		{
			// 행렬식이 0인 경우엔 역행렬이 존재하지 않음.
			return result;
		}

		float invDet = 1.0f / det;

		/// SIMD를 활용한 역행렬 구하는 방법을 찾아봤는데
		/// 어셈블리어 밖에 없어서 포기함.

		result.e00 = (e12 * e23 * e31 - e13 * e22 * e31 + e13 * e21 * e32 - e11 * e23 * e32 - e12 * e21 * e33 + e11 * e22 * e33) * invDet;
		result.e01 = (e03 * e22 * e31 - e02 * e23 * e31 - e03 * e21 * e32 + e01 * e23 * e32 + e02 * e21 * e33 - e01 * e22 * e33) * invDet;
		result.e02 = (e02 * e13 * e31 - e03 * e12 * e31 + e03 * e11 * e32 - e01 * e13 * e32 - e02 * e11 * e33 + e01 * e12 * e33) * invDet;
		result.e03 = (e03 * e12 * e21 - e02 * e13 * e21 - e03 * e11 * e22 + e01 * e13 * e22 + e02 * e11 * e23 - e01 * e12 * e23) * invDet;
		result.e10 = (e13 * e22 * e30 - e12 * e23 * e30 - e13 * e20 * e32 + e10 * e23 * e32 + e12 * e20 * e33 - e10 * e22 * e33) * invDet;
		result.e11 = (e02 * e23 * e30 - e03 * e22 * e30 + e03 * e20 * e32 - e00 * e23 * e32 - e02 * e20 * e33 + e00 * e22 * e33) * invDet;
		result.e12 = (e03 * e12 * e30 - e02 * e13 * e30 - e03 * e10 * e32 + e00 * e13 * e32 + e02 * e10 * e33 - e00 * e12 * e33) * invDet;
		result.e13 = (e02 * e13 * e20 - e03 * e12 * e20 + e03 * e10 * e22 - e00 * e13 * e22 - e02 * e10 * e23 + e00 * e12 * e23) * invDet;
		result.e20 = (e11 * e23 * e30 - e13 * e21 * e30 + e13 * e20 * e31 - e10 * e23 * e31 - e11 * e20 * e33 + e10 * e21 * e33) * invDet;
		result.e21 = (e03 * e21 * e30 - e01 * e23 * e30 - e03 * e20 * e31 + e00 * e23 * e31 + e01 * e20 * e33 - e00 * e21 * e33) * invDet;
		result.e22 = (e01 * e13 * e30 - e03 * e11 * e30 + e03 * e10 * e31 - e00 * e13 * e31 - e01 * e10 * e33 + e00 * e11 * e33) * invDet;
		result.e23 = (e03 * e11 * e20 - e01 * e13 * e20 - e03 * e10 * e21 + e00 * e13 * e21 + e01 * e10 * e23 - e00 * e11 * e23) * invDet;
		result.e30 = (e12 * e21 * e30 - e11 * e22 * e30 - e12 * e20 * e31 + e10 * e22 * e31 + e11 * e20 * e32 - e10 * e21 * e32) * invDet;
		result.e31 = (e01 * e22 * e30 - e02 * e21 * e30 + e02 * e20 * e31 - e00 * e22 * e31 - e01 * e20 * e32 + e00 * e21 * e32) * invDet;
		result.e32 = (e02 * e11 * e30 - e01 * e12 * e30 - e02 * e10 * e31 + e00 * e12 * e31 + e01 * e10 * e32 - e00 * e11 * e32) * invDet;
		result.e33 = (e01 * e12 * e20 - e02 * e11 * e20 + e02 * e10 * e21 - e00 * e12 * e21 - e01 * e10 * e22 + e00 * e11 * e22) * invDet;

		return result;
	}

	Vector3D Matrix4x4::Right() const noexcept
	{
        if (e00 == 0.f && e01 == 0.f && e02 == 0.f)
        {
            return Vector3D(1.f, 0.f, 0.f);
        }

		return Vector3D(e00, e01, e02);
	}

	Vector3D Matrix4x4::Up() const noexcept
    {
        if (e10 == 0.f && e11 == 0.f && e12 == 0.f)
        {
            return Vector3D(0.f, 1.f, 0.f);
        }

		return Vector3D(e10, e11, e12);
	}

	Vector3D Matrix4x4::Look() const noexcept
	{
        if (e20 == 0.f && e21 == 0.f && e22 == 0.f)
        {
            return Vector3D(0.f, 0.f, 1.f);
        }

		return Vector3D(e20, e21, e22);
	}

	Vector3D Matrix4x4::Pos() const noexcept
	{
		return Vector3D(e30, e31, e32);
	}

	float Matrix4x4::Determinant() const noexcept
	{
		float det =
			e00 * e11 * e22 * e33 + 
			e00 * e12 * e23 * e31 + 
			e00 * e13 * e21 * e32 + 
			e01 * e10 * e23 * e32 + 
			e01 * e12 * e20 * e33 + 
			e01 * e13 * e22 * e30 + 
			e02 * e10 * e21 * e33 + 
			e02 * e11 * e23 * e30 + 
			e02 * e13 * e20 * e31 + 
			e03 * e10 * e22 * e31 + 
			e03 * e11 * e20 * e32 + 
			e03 * e12 * e21 * e30 - 
			e00 * e11 * e23 * e32 - 
			e00 * e12 * e21 * e33 - 
			e00 * e13 * e22 * e31 - 
			e01 * e10 * e22 * e33 - 
			e01 * e12 * e23 * e30 -
			e01 * e13 * e20 * e32 - 
			e02 * e10 * e23 * e31 - 
			e02 * e11 * e20 * e33 - 
			e02 * e13 * e21 * e30 - 
			e03 * e10 * e21 * e32 - 
			e03 * e11 * e22 * e30 - 
			e03 * e12 * e20 * e31;


		return det;
	}

	float Matrix4x4::Determinant3x3() const noexcept
	{
		return 
			e00 * (e11 * e22 - e12 * e21) -
			e01 * (e10 * e22 - e12 * e20) +
			e02 * (e10 * e21 - e11 * e20);
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) noexcept
	{
#ifdef _PHYSICS
		this->m[0] += other.m[0];
		this->m[1] += other.m[1];
		this->m[2] += other.m[2];
		this->m[3] += other.m[3];
#else
        this->e00 += other.e00;
        this->e01 += other.e01;
        this->e02 += other.e02;
        this->e03 += other.e03;

        this->e10 += other.e10;
        this->e11 += other.e11;
        this->e12 += other.e12;
        this->e13 += other.e13;

        this->e20 += other.e20;
        this->e21 += other.e21;
        this->e22 += other.e22;
        this->e23 += other.e23;

        this->e30 += other.e30;
        this->e31 += other.e31;
        this->e32 += other.e32;
        this->e33 += other.e33;
#endif

		return *this;
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) noexcept
	{
#ifdef _PHYSICS
        this->m[0] -= other.m[0];
        this->m[1] -= other.m[1];
        this->m[2] -= other.m[2];
        this->m[3] -= other.m[3];
#else
        this->e00 -= other.e00;
        this->e01 -= other.e01;
        this->e02 -= other.e02;
        this->e03 -= other.e03;

        this->e10 -= other.e10;
        this->e11 -= other.e11;
        this->e12 -= other.e12;
        this->e13 -= other.e13;

        this->e20 -= other.e20;
        this->e21 -= other.e21;
        this->e22 -= other.e22;
        this->e23 -= other.e23;

        this->e30 -= other.e30;
        this->e31 -= other.e31;
        this->e32 -= other.e32;
        this->e33 -= other.e33;
#endif

        return *this;
	}

	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const noexcept
	{
		Matrix4x4 temp(*this);

		return temp += other;
	}

	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const noexcept
	{
		Matrix4x4 temp(*this);

		return temp -= other;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const noexcept
	{
		Matrix4x4 temp(*this);

		return temp *= other;
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) noexcept
	{
#ifdef _PHYSICS
		Matrix4x4 temp
		(
			other.e00, other.e10, other.e20, other.e30,
			other.e01, other.e11, other.e21, other.e31,
			other.e02, other.e12, other.e22, other.e32,
			other.e03, other.e13, other.e23, other.e33
		);

		__m128 m0{ this->m[0].m };
		__m128 m1{ this->m[1].m };
		__m128 m2{ this->m[2].m };
		__m128 m3{ this->m[3].m };

		// 행렬 연산은 내적과 비슷하다...
		this->e00 = _mm_cvtss_f32(_mm_dp_ps(m0, temp.m[0].m, 0xff));
		this->e01 = _mm_cvtss_f32(_mm_dp_ps(m0, temp.m[1].m, 0xff));
		this->e02 = _mm_cvtss_f32(_mm_dp_ps(m0, temp.m[2].m, 0xff));
		this->e03 = _mm_cvtss_f32(_mm_dp_ps(m0, temp.m[3].m, 0xff));
		
		this->e10 = _mm_cvtss_f32(_mm_dp_ps(m1, temp.m[0].m, 0xff));
		this->e11 = _mm_cvtss_f32(_mm_dp_ps(m1, temp.m[1].m, 0xff));
		this->e12 = _mm_cvtss_f32(_mm_dp_ps(m1, temp.m[2].m, 0xff));
		this->e13 = _mm_cvtss_f32(_mm_dp_ps(m1, temp.m[3].m, 0xff));
		
		this->e20 = _mm_cvtss_f32(_mm_dp_ps(m2, temp.m[0].m, 0xff));
		this->e21 = _mm_cvtss_f32(_mm_dp_ps(m2, temp.m[1].m, 0xff));
		this->e22 = _mm_cvtss_f32(_mm_dp_ps(m2, temp.m[2].m, 0xff));
		this->e23 = _mm_cvtss_f32(_mm_dp_ps(m2, temp.m[3].m, 0xff));
		
		this->e30 = _mm_cvtss_f32(_mm_dp_ps(m3, temp.m[0].m, 0xff));
		this->e31 = _mm_cvtss_f32(_mm_dp_ps(m3, temp.m[1].m, 0xff));
		this->e32 = _mm_cvtss_f32(_mm_dp_ps(m3, temp.m[2].m, 0xff));
		this->e33 = _mm_cvtss_f32(_mm_dp_ps(m3, temp.m[3].m, 0xff));
#else
        Matrix4x4 result(*this);

        this->e00 = result.e00 * other.e00 + result.e01 * other.e10 + result.e02 * other.e20 + result.e03 * other.e30;
        this->e01 = result.e00 * other.e01 + result.e01 * other.e11 + result.e02 * other.e21 + result.e03 * other.e31;
        this->e02 = result.e00 * other.e02 + result.e01 * other.e12 + result.e02 * other.e22 + result.e03 * other.e32;
        this->e03 = result.e00 * other.e03 + result.e01 * other.e13 + result.e02 * other.e23 + result.e03 * other.e33;

        this->e10 = result.e10 * other.e00 + result.e11 * other.e10 + result.e12 * other.e20 + result.e13 * other.e30;
        this->e11 = result.e10 * other.e01 + result.e11 * other.e11 + result.e12 * other.e21 + result.e13 * other.e31;
        this->e12 = result.e10 * other.e02 + result.e11 * other.e12 + result.e12 * other.e22 + result.e13 * other.e32;
        this->e13 = result.e10 * other.e03 + result.e11 * other.e13 + result.e12 * other.e23 + result.e13 * other.e33;

        this->e20 = result.e20 * other.e00 + result.e21 * other.e10 + result.e22 * other.e20 + result.e23 * other.e30;
        this->e21 = result.e20 * other.e01 + result.e21 * other.e11 + result.e22 * other.e21 + result.e23 * other.e31;
        this->e22 = result.e20 * other.e02 + result.e21 * other.e12 + result.e22 * other.e22 + result.e23 * other.e32;
        this->e23 = result.e20 * other.e03 + result.e21 * other.e13 + result.e22 * other.e23 + result.e23 * other.e33;

        this->e30 = result.e30 * other.e00 + result.e31 * other.e10 + result.e32 * other.e20 + result.e33 * other.e30;
        this->e31 = result.e30 * other.e01 + result.e31 * other.e11 + result.e32 * other.e21 + result.e33 * other.e31;
        this->e32 = result.e30 * other.e02 + result.e31 * other.e12 + result.e32 * other.e22 + result.e33 * other.e32;
        this->e33 = result.e30 * other.e03 + result.e31 * other.e13 + result.e32 * other.e23 + result.e33 * other.e33;
#endif

		return *this;
	}

	bool Matrix4x4::operator==(const Matrix4x4& _mat) noexcept
	{
#ifdef _PHYSICS
		return (this->m[0] == _mat.m[0]) && (this->m[1] == _mat.m[1]) && (this->m[2] == _mat.m[2]) && (this->m[3] == _mat.m[3]);
#else
        return (
            e00 == _mat.e00 && e01 == _mat.e01 && e02 == _mat.e02 && e03 == _mat.e03 &&
            e10 == _mat.e10 && e11 == _mat.e11 && e12 == _mat.e12 && e13 == _mat.e13 &&
            e20 == _mat.e20 && e21 == _mat.e21 && e22 == _mat.e22 && e23 == _mat.e23 &&
            e30 == _mat.e30 && e31 == _mat.e31 && e32 == _mat.e32 && e33 == _mat.e33
            );
#endif
    }
}