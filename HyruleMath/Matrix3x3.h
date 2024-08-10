#pragma once
#include "Matrix1x3.h"

namespace Hyrule
{
	struct Vector3D;
	struct Matrix1x3;

	struct Matrix3x3
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		constexpr Matrix3x3() noexcept :
#ifdef _PHYSICS
			e{}
#else
            e00(), e01(), e02(),
            e10(), e11(), e12(),
            e20(), e21(), e22()
#endif
		{}
		constexpr Matrix3x3(
			float _e00, float _e01, float _e02,
			float _e10, float _e11, float _e12,
			float _e20, float _e21, float _e22) noexcept :
#ifdef _PHYSICS
			e
			{
				_e00, _e01, _e02,
				_e10, _e11, _e12,
				_e20, _e21, _e22
			}
#else
            e00(_e00), e01(_e01), e02(_e02),
            e10(_e10), e11(_e11), e12(_e12),
            e20(_e20), e21(_e21), e22(_e22)
#endif
		{}
		constexpr Matrix3x3(
			const Matrix1x3& _m1,
			const Matrix1x3& _m2,
			const Matrix1x3& _m3) noexcept :
#ifdef _PHYSICS
			e
		{
			_m1.e00, _m1.e01, _m1.e02,
			_m2.e00, _m2.e01, _m2.e02,
			_m3.e00, _m3.e01, _m3.e02,
		}
#else
            e00(_m1.e00), e01(_m1.e01), e02(_m1.e02),
            e10(_m2.e00), e11(_m2.e01), e12(_m2.e02),
            e20(_m3.e00), e21(_m3.e01), e22(_m3.e02)
#endif
		{}
		constexpr Matrix3x3(const Matrix3x3&) noexcept = default;
		constexpr Matrix3x3(Matrix3x3&&) noexcept = default;

        constexpr Matrix3x3(const float _n) noexcept :
#ifdef _PHYSICS
            e
        {
            _n, _n, _n,
            _n, _n, _n,
            _n, _n, _n
        }
#else
            e00(_n), e01(_n), e02(_n),
            e10(_n), e11(_n), e12(_n),
            e20(_n), e21(_n), e22(_n)
#endif
        {}
		~Matrix3x3() noexcept = default;

		constexpr Matrix3x3& operator= (const Matrix3x3&) noexcept = default;
		constexpr Matrix3x3& operator= (Matrix3x3&&) noexcept = default;

		/// <summary>
		/// 멤버 변수
		/// </summary>
#ifdef _PHYSICS
		union
		{
			struct
			{
#endif
				float e00, e01, e02, e10, e11, e12, e20, e21, e22;
#ifdef _PHYSICS
			};
			struct 
			{
				float Ixx, Ixy, Ixz, Iyx, Iyy, Iyz, Izx, Izy, Izz;
			};
			float e[3][3];
		};
#endif

		/// <summary>
		/// 전역 함수
		/// </summary>
		static inline Matrix3x3 Identity() noexcept
		{
			return Matrix3x3
			{
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				0.f, 0.f, 1.f,
			};
		}

		static inline Matrix3x3 Zero() noexcept
		{
			return Matrix3x3{};
		}

		/// <summary>
		/// 멤버 함수
		/// </summary>
		float Determinant() noexcept;
		Matrix3x3 Transpose() noexcept;
		Matrix3x3 Inverse() noexcept;

		/// <summary>
		/// 연산자 오버로딩
		/// </summary>
		Matrix3x3 operator+ (const Matrix3x3&) const noexcept;
		Matrix3x3& operator+= (const Matrix3x3&) noexcept;
		Matrix3x3 operator- (const Matrix3x3&) const noexcept;
		Matrix3x3& operator-= (const Matrix3x3&) noexcept;
		Matrix3x3 operator* (const Matrix3x3&) const noexcept;
		Matrix3x3& operator*= (const Matrix3x3&) noexcept;

		bool operator== (const Matrix3x3&) const noexcept;
		// Matrix3x3 operator/ (const Matrix3x3&) const noexcept;
		// Matrix3x3& operator/= (const Matrix3x3&) noexcept;
	};
}