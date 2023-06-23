#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Matrix1x4;

	struct Quaternion
	{
		/// <summary>
		/// 특수 멤버 함수
		/// </summary>
		Quaternion() noexcept = default;
		Quaternion(float, float, float, float) noexcept;
		Quaternion(const Quaternion& other) noexcept = default;
		Quaternion(Quaternion&& other) noexcept = default;
		~Quaternion() noexcept = default;

		Quaternion& operator= (const Quaternion&) noexcept = default;
		Quaternion& operator= (Quaternion&&) noexcept = default;

		/// <summary>
		/// 멤버 변수
		/// </summary>
		union
		{
			struct
			{
				float x, y, z, w;
			};
			float e[4];
		};

		static inline Quaternion Identity() noexcept;

		/// <summary>
		/// 쿼터니언 함수
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		Quaternion Conjugate() const noexcept;
		Quaternion Inverse() const noexcept;
		Quaternion& Normalize() noexcept;
		Quaternion Normalized() const noexcept;
		Matrix1x4 ToMatrix() const noexcept;
		Vector3D RotateVector(const Vector3D& vector) const noexcept;

		/// <summary>
		/// 연산자 오버로딩
		/// </summary>
		Quaternion& operator += (const Quaternion&) noexcept;
		Quaternion& operator -= (const Quaternion&) noexcept;

		Quaternion operator + (const Quaternion&) const noexcept;
		Quaternion operator - (const Quaternion&) const noexcept;
		Quaternion operator - () const noexcept;

		Quaternion& operator *= (const float) noexcept;
		Quaternion& operator /= (const float) noexcept;

		Quaternion operator * (const float) const noexcept;
		Quaternion operator / (const float) const noexcept;

		bool operator == (const Quaternion&) const noexcept;
	};

	// Quaternion을 사용한 함수 예시
	Quaternion Slerp(const Quaternion& start, const Quaternion& end, float t);
	Quaternion RotationBetweenVectors(const Vector3D& from, const Vector3D& to);
}

