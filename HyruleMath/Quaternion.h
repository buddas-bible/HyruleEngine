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
		/// Ư�� ��� �Լ�
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
		/// ��� ����
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
		/// ���ʹϾ� �Լ�
		/// </summary>
		float Length() const noexcept;
		float LengthSquare() const noexcept;
		float FastInvSqrt(float) const noexcept;
		float Dot(const Quaternion&) const noexcept;

		Quaternion Conjugate() const noexcept;
		Quaternion Inverse() const noexcept;
		Quaternion& Normalize() noexcept;
		Quaternion Normalized() const noexcept;

		// ���� �Լ� �������� �ñ� ����
		Vector3D ToEuler() const noexcept;
		Vector4D ToAxisAngle() const noexcept;
		Matrix4x4 ToMatrix() const noexcept;

		/// <summary>
		/// ������ �����ε�
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

	// ����� ���� �Լ�
// 	Quaternion Lerp(const Quaternion&, const Quaternion&, float) noexcept;
// 	Quaternion Slerp(const Quaternion&, const Quaternion&, float) noexcept;
// 
// 	Quaternion ToQuaternion(const Vector3D&) noexcept;
// 	Quaternion ToQuaternion(const Vector4D&) noexcept;
// 	Quaternion ToQuaternion(const Matrix4x4&) noexcept;
}

