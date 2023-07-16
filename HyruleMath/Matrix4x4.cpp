// #include "Vector4D.h"

#include "Matrix4x4.h"

namespace Hyrule
{
	// 	constexpr Matrix4x4::Matrix4x4() noexcept : 
	// 		m()
	// 	{
	// 
	// 	}
 
 // 	constexpr Matrix4x4::Matrix4x4(
 // 		float _e00, float _e01, float _e02, float _e03,
 // 		float _e10, float _e11, float _e12, float _e13,
 // 		float _e20, float _e21, float _e22, float _e23,
 // 		float _e30, float _e31, float _e32, float _e33) noexcept :
 // 		e
 // 		{ 
 // 			_e00, _e01, _e02, _e03,
 // 			_e10, _e11, _e12, _e13,
 // 			_e20, _e21, _e22, _e23,
 // 			_e30, _e31, _e32, _e33
 // 		}
 // 	{
 // 
 // 	}


// 	constexpr Matrix4x4::Matrix4x4(
// 		const Matrix1x4& _m1,
// 		const Matrix1x4& _m2,
// 		const Matrix1x4& _m3,
// 		const Matrix1x4& _m4) noexcept : 
// 		m
// 		{ 
// 			_m1, _m2, _m3, _m4 
// 		}
// 	{
// 
// 	}

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
			// ��Ľ��� 0�� ��쿣 ������� �������� ����.
			return result;
		}

		float invDet = 1.0f / det;

		/// SIMD�� Ȱ���� ����� ���ϴ� ����� ã�ƺôµ�
		/// ������� �ۿ� ��� ������.

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
			e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]) -
			e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0]) +
			e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) noexcept
	{
		this->m[0] += other.m[0];
		this->m[1] += other.m[1];
		this->m[2] += other.m[2];
		this->m[3] += other.m[3];

		return *this;
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) noexcept
	{
		this->m[0] -= other.m[0];
		this->m[1] -= other.m[1];
		this->m[2] -= other.m[2];
		this->m[3] -= other.m[3];

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

		// ��� ������ ������ ����ϴ�...
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

		// this->e00 = temp.e[0][0] * other.e[0][0] + temp.e[0][1] * other.e[1][0] + temp.e[0][2] * other.e[2][0] + temp.e[0][3] * other.e[3][0];
		// this->e01 = temp.e[0][0] * other.e[0][1] + temp.e[0][1] * other.e[1][1] + temp.e[0][2] * other.e[2][1] + temp.e[0][3] * other.e[3][1];
		// this->e02 = temp.e[0][0] * other.e[0][2] + temp.e[0][1] * other.e[1][2] + temp.e[0][2] * other.e[2][2] + temp.e[0][3] * other.e[3][2];
		// this->e03 = temp.e[0][0] * other.e[0][3] + temp.e[0][1] * other.e[1][3] + temp.e[0][2] * other.e[2][3] + temp.e[0][3] * other.e[3][3];
		// 
		// this->e10 = temp.e[1][0] * other.e[0][0] + temp.e[1][1] * other.e[1][0] + temp.e[1][2] * other.e[2][0] + temp.e[1][3] * other.e[3][0];
		// this->e11 = temp.e[1][0] * other.e[0][1] + temp.e[1][1] * other.e[1][1] + temp.e[1][2] * other.e[2][1] + temp.e[1][3] * other.e[3][1];
		// this->e12 = temp.e[1][0] * other.e[0][2] + temp.e[1][1] * other.e[1][2] + temp.e[1][2] * other.e[2][2] + temp.e[1][3] * other.e[3][2];
		// this->e13 = temp.e[1][0] * other.e[0][3] + temp.e[1][1] * other.e[1][3] + temp.e[1][2] * other.e[2][3] + temp.e[1][3] * other.e[3][3];
		// 
		// this->e20 = temp.e[2][0] * other.e[0][0] + temp.e[2][1] * other.e[1][0] + temp.e[2][2] * other.e[2][0] + temp.e[2][3] * other.e[3][0];
		// this->e21 = temp.e[2][0] * other.e[0][1] + temp.e[2][1] * other.e[1][1] + temp.e[2][2] * other.e[2][1] + temp.e[2][3] * other.e[3][1];
		// this->e22 = temp.e[2][0] * other.e[0][2] + temp.e[2][1] * other.e[1][2] + temp.e[2][2] * other.e[2][2] + temp.e[2][3] * other.e[3][2];
		// this->e23 = temp.e[2][0] * other.e[0][3] + temp.e[2][1] * other.e[1][3] + temp.e[2][2] * other.e[2][3] + temp.e[2][3] * other.e[3][3];
		// 
		// this->e30 = temp.e[3][0] * other.e[0][0] + temp.e[3][1] * other.e[1][0] + temp.e[3][2] * other.e[2][0] + temp.e[3][3] * other.e[3][0];
		// this->e31 = temp.e[3][0] * other.e[0][1] + temp.e[3][1] * other.e[1][1] + temp.e[3][2] * other.e[2][1] + temp.e[3][3] * other.e[3][1];
		// this->e32 = temp.e[3][0] * other.e[0][2] + temp.e[3][1] * other.e[1][2] + temp.e[3][2] * other.e[2][2] + temp.e[3][3] * other.e[3][2];
		// this->e33 = temp.e[3][0] * other.e[0][3] + temp.e[3][1] * other.e[1][3] + temp.e[3][2] * other.e[2][3] + temp.e[3][3] * other.e[3][3];

		return *this;
	}
}