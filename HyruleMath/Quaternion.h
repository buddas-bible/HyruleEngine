#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix1x4;
	struct Matrix4x4;

	struct Quaternion
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		Quaternion() noexcept = default;
		Quaternion(float, float, float, float) noexcept;
		Quaternion(const Quaternion&) noexcept = default;
		Quaternion(Quaternion&&) noexcept = default;
		~Quaternion() noexcept = default;

		Quaternion& operator= (const Quaternion&) noexcept = default;
		Quaternion& operator= (Quaternion&&) noexcept = default;

		explicit operator Matrix1x4() noexcept;
		explicit operator Vector4D() noexcept;

		/// <summary>
		/// 멤버 변수
		/// </summary>
		union
		{
			struct
			{
				float w, x, y, z;
			};
			float e[4];
		};

		static inline Quaternion Identity() noexcept;

		/// <summary>
		/// 쿼터니언 함수
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		float FastInvSqrt(float) const noexcept;
		float Dot(const Quaternion&) const noexcept;

		Quaternion Conjugate() const noexcept;
		Quaternion Inverse() const noexcept;
		Quaternion& Normalize() noexcept;
		Quaternion Normalized() const noexcept;

		// 수학 함수 모음으로 올길 예정
		Vector3D ToEuler() const noexcept;
		Vector4D ToAxisAngle() const noexcept;
		Matrix4x4 ToMatrix() const noexcept;

		/// <summary>
		/// 연산자 오버로딩
		/// </summary>
		Quaternion& operator += (const Quaternion&) noexcept;
		Quaternion& operator -= (const Quaternion&) noexcept;

		Quaternion operator + (const Quaternion&) const noexcept;
		Quaternion operator - (const Quaternion&) const noexcept;
		Quaternion operator - () const noexcept;

		Quaternion& operator *= (const Quaternion&) noexcept;
		Quaternion& operator /= (const Quaternion&) noexcept;

		Quaternion operator * (const Quaternion&) const noexcept;
		Quaternion operator / (const Quaternion&) const noexcept;

		Quaternion& operator *= (const float) noexcept;
		Quaternion& operator /= (const float) noexcept;

		Quaternion operator * (const float) const noexcept;
		Quaternion operator / (const float) const noexcept;

		friend Quaternion& operator *= (const float, const Quaternion&) noexcept;
		friend Quaternion& operator /= (const float, const Quaternion&) noexcept;

		friend Quaternion operator * (const float, const Quaternion&) noexcept;
		friend Quaternion operator / (const float, const Quaternion&) noexcept;

		bool operator == (const Quaternion&) const noexcept;
	};

	Quaternion& operator *= (const float, const Quaternion&) noexcept;
	Quaternion& operator /= (const float, const Quaternion&) noexcept;
	Quaternion operator * (const float, const Quaternion&) noexcept;
	Quaternion operator / (const float, const Quaternion&) noexcept;

	// 사원수 보간 함수
// 	Quaternion Lerp(const Quaternion&, const Quaternion&, float) noexcept;
// 	Quaternion Slerp(const Quaternion&, const Quaternion&, float) noexcept;
// 
// 	Quaternion ToQuaternion(const Vector3D&) noexcept;
// 	Quaternion ToQuaternion(const Vector4D&) noexcept;
// 	Quaternion ToQuaternion(const Matrix4x4&) noexcept;
}

