#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Matrix1x4;

	struct Quaternion
	{
		/// <summary>
		/// Ư�� ��� �Լ�
		/// </summary>
		Quaternion() noexcept = default;
		Quaternion(float, float, float, float) noexcept;
		Quaternion(const Quaternion& other) noexcept = default;
		Quaternion(Quaternion&& other) noexcept = default;
		~Quaternion() noexcept = default;

		Quaternion& operator= (const Quaternion&) noexcept = default;
		Quaternion& operator= (Quaternion&&) noexcept = default;

		/// <summary>
		/// ��� ����
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
		/// ���ʹϾ� �Լ�
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
		/// ������ �����ε�
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

	// Quaternion�� ����� �Լ� ����
	Quaternion Slerp(const Quaternion& start, const Quaternion& end, float t);
	Quaternion RotationBetweenVectors(const Vector3D& from, const Vector3D& to);
}

